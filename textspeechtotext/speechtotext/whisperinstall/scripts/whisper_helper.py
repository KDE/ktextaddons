#!/usr/bin/env python3
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: LGPL-2.0-or-later
"""Whisper speech-to-text helper.

Standalone test tool and, in ``serve`` mode, the backend process driven over a
pipe by the Qt WhisperSpeechToTextPlugin: the plugin pushes the PCM captured by
QAudioSource, the script answers with text.

Requires ``pip install faster-whisper`` (pulls in ctranslate2, tokenizers and
numpy). No PyTorch and no espeak-ng are needed. The model itself is fetched
from HuggingFace on first use and cached in ~/.cache/huggingface.

Whisper transcribes complete utterances, not a stream: the incoming audio is
cut on silence (see Endpointer) and each utterance is handed to the model as a
whole. The latency is therefore the silence timeout plus the decoding time, not
the vosk-like word-by-word output.

Examples:
    whisper_helper.py check
    whisper_helper.py models
    whisper_helper.py download --model small   # json progress on stdout
    whisper_helper.py download --all           # what is in the cache already
    whisper_helper.py transcribe --file /tmp/hello.wav --language fr
    whisper_helper.py serve      # newline-delimited JSON on stdin, frames on stdout
"""

import argparse
import importlib.util
import json
import os
import queue
import sys
import threading
import wave
from collections import deque

SAMPLE_RATE = 16000
CHANNELS = 1

DEFAULT_MODEL = "small"
# int8 is what makes the medium models usable on a plain CPU; float32 is only
# worth it on a GPU.
DEFAULT_COMPUTE_TYPE = "int8"
DEFAULT_DEVICE = "cpu"
BEAM_SIZE = 5

# The models of the openai/faster-whisper family, with the disk footprint of the
# ctranslate2 conversion, so that the engine can show it before downloading.
# "distil" models are english only but roughly twice as fast.
MODELS = (
    ("tiny", 75, True),
    ("base", 145, True),
    ("small", 490, True),
    ("medium", 1530, True),
    ("large-v3", 3090, True),
    ("distil-small.en", 340, False),
    ("distil-medium.en", 790, False),
    ("distil-large-v3", 1510, False),
)

# The pip name is not the module name for every dependency.
PIP_NAMES = {"faster_whisper": "faster-whisper"}
REQUIRED_MODULES = ("faster_whisper", "numpy")

# --- endpointing ------------------------------------------------------------
#
# Deliberately energy based: a real VAD (silero, webrtcvad) would be one more
# dependency, and faster-whisper already runs its own VAD on what it is given.
# The values below are what dictation in a quiet room needs.

# Audio is analysed by frames of that duration, in seconds.
FRAME_DURATION = 0.02
# RMS below which a frame is considered silent, 0.0 to 1.0 (~ -40 dBFS).
SILENCE_THRESHOLD = 0.01
# Silence closing an utterance, in seconds.
SILENCE_DURATION = 0.8
# Utterances shorter than that are dropped: whisper hallucinates on a click.
MIN_SPEECH_DURATION = 0.3
# Whisper decodes windows of 30s, so an utterance is cut before that.
MAX_SEGMENT_DURATION = 25.0
# Audio kept before speech is detected, so the first phoneme is not clipped.
PREROLL_DURATION = 0.3
# Audio kept after the last voiced frame, so the last consonant is not cut.
TAIL_DURATION = 0.2
# Minimum audio added before a new partial result is worth computing.
PARTIAL_INTERVAL = 1.0


def log(*args):
    print(*args, file=sys.stderr, flush=True)


def availability():
    """Report what is installed without importing the heavy libraries."""
    missing = [
        PIP_NAMES.get(name, name)
        for name in REQUIRED_MODULES
        if not importlib.util.find_spec(name)
    ]
    return {
        "available": not missing,
        "missing": missing,
        "python": sys.executable,
        "sampleRate": SAMPLE_RATE,
        "channels": CHANNELS,
    }


def model_table():
    return [
        {
            "id": name,
            "name": name,
            "sizeMib": size,
            "multilingual": multilingual,
            "default": name == DEFAULT_MODEL,
        }
        for name, size, multilingual in MODELS
    ]


# --- model download --------------------------------------------------------
#
# WhisperModel() downloads what it needs by itself, but it does so in the middle
# of the first transcription and says nothing while it goes: 490 MiB for the
# default model, during which the engine looks hung. This is the same download,
# asked for on its own, reporting one json line per event on stdout:
#
#   {"type": "start", "model": "small", "repo": "Systran/faster-whisper-small"}
#   {"type": "progress", "model": "small", "received": 1234, "total": 5678, "percent": 21}
#   {"type": "finished", "model": "small", "path": "/home/.../snapshots/..."}
#
# plus "cached" when there is nothing to download, "missing" for --dry-run and
# "error" for anything which went wrong.
#
# --all downloads nothing: it answers one "cached" or "missing" line per model of
# the table, which is what fills the model list of the engine.

# The files faster_whisper.utils.download_model asks for: the same ones have to
# be in the cache for WhisperModel() not to download anything afterwards.
MODEL_FILES = (
    "config.json",
    "preprocessor_config.json",
    "model.bin",
    "tokenizer.json",
    "vocabulary.*",
)

# huggingface_hub counts the same bytes twice: once as they are received from
# the network, once as they are written to disk. The second bar only moves when
# a file is complete, which for a model made of one big file means 0 % then
# 100 %, so the one followed here is the network one.
RECONSTRUCT_BAR_DESC = "Reconstructing"


def report(**event):
    """One json line on stdout, which is what the engine reads."""
    print(json.dumps(event, ensure_ascii=False), flush=True)


def model_repository(name):
    """Repository of the hub a model is downloaded from, None when unknown."""
    if "/" in name:
        # A ctranslate2 model given by its full id, not one of the table.
        return name
    from faster_whisper.utils import _MODELS

    return _MODELS.get(name)


class DownloadProgress:
    """Sums what the bars of huggingface_hub report, and says it in percent."""

    def __init__(self, model):
        self._model = model
        self._bars = {}
        self._percent = None
        self._lock = threading.Lock()

    def update(self, bar, received, total):
        with self._lock:
            self._bars[bar] = (received, total or 0)
            received = sum(value[0] for value in self._bars.values())
            total = sum(value[1] for value in self._bars.values())
            percent = int(received * 100 / total) if total else 0
            # One line per percent: a line per chunk would be thousands of them.
            if percent == self._percent:
                return
            # A full bar is what "finished" means. Before it, it only means that
            # a small file is done and that the big one has not announced its
            # size yet, or that deduplication spared bytes which were counted.
            if percent >= 100:
                return
            self._percent = percent
            report(
                type="progress",
                model=self._model,
                received=received,
                total=total,
                percent=percent,
            )


def progress_tqdm_class(progress):
    """The bar class huggingface_hub drives, reporting to \a progress."""
    from huggingface_hub.utils import tqdm as hf_tqdm

    class ProgressTqdm(hf_tqdm):
        def __init__(self, *args, **kwargs):
            # tqdm drops its arguments when the bar is disabled, which it is when
            # nothing is attached to a terminal, so they are kept here.
            self._reported = kwargs.get("unit") == "B" and not (
                kwargs.get("desc") or ""
            ).startswith(RECONSTRUCT_BAR_DESC)
            self._received = 0
            super().__init__(*args, **kwargs)

        def update(self, n=1):
            # self.n is not moved by a disabled bar: the count is our own.
            self._received += n or 0
            if self._reported:
                progress.update(id(self), self._received, self.total)
            return super().update(n)

    return ProgressTqdm


def cached_model_path(repo_id):
    """Where the model is, when all of its files are already in the cache."""
    from huggingface_hub import snapshot_download

    try:
        return snapshot_download(
            repo_id, allow_patterns=list(MODEL_FILES), local_files_only=True
        )
    except Exception:  # noqa: BLE001 - not cached, or not cached completely
        return None


def report_model_state(name):
    """Says whether \a name is in the cache, without downloading anything."""
    repo_id = model_repository(name)
    if repo_id is None:
        report(type="error", model=name, message=f"unknown model: {name!r}")
        return False
    if (path := cached_model_path(repo_id)) is not None:
        report(type="cached", model=name, repo=repo_id, path=path)
        return True
    sizes = {model: size for model, size, _ in MODELS}
    report(type="missing", model=name, repo=repo_id, sizeMib=sizes.get(name, 0))
    return True


def download(args):
    from huggingface_hub import snapshot_download

    # Asking model by model would be one interpreter start per model, and the
    # engine wants the state of the whole table to show it in one list.
    if args.all:
        ok = all([report_model_state(name) for name, _, _ in MODELS])
        return 0 if ok else 1

    repo_id = model_repository(args.model)
    if repo_id is None:
        report(
            type="error",
            model=args.model,
            message=f"unknown model: {args.model!r}",
        )
        return 1
    if not args.force:
        if (path := cached_model_path(repo_id)) is not None:
            report(type="cached", model=args.model, repo=repo_id, path=path)
            return 0
    if args.dry_run:
        sizes = {name: size for name, size, _ in MODELS}
        report(
            type="missing",
            model=args.model,
            repo=repo_id,
            sizeMib=sizes.get(args.model, 0),
        )
        return 0

    report(type="start", model=args.model, repo=repo_id)
    progress = DownloadProgress(args.model)
    try:
        path = snapshot_download(
            repo_id,
            allow_patterns=list(MODEL_FILES),
            force_download=args.force,
            tqdm_class=progress_tqdm_class(progress),
        )
    except Exception as error:  # noqa: BLE001 - network, disk, offline mode...
        report(
            type="error",
            model=args.model,
            repo=repo_id,
            message=f"{type(error).__name__}: {error}",
        )
        return 1
    report(type="finished", model=args.model, repo=repo_id, path=path)
    return 0


def pcm_to_float(payload, sample_format="int16"):
    """Convert raw little-endian PCM to the float32 array whisper expects."""
    import numpy as np

    if sample_format == "float":
        return np.frombuffer(payload, dtype="<f4").astype(np.float32, copy=False)
    samples = np.frombuffer(payload, dtype="<i2").astype(np.float32)
    return samples / 32768.0


class Endpointer:
    """Cuts the incoming stream into utterances on silence.

    A short pre-roll is kept so that the beginning of the first word survives
    the detection delay.
    """

    def __init__(
        self,
        sample_rate=SAMPLE_RATE,
        silence_threshold=SILENCE_THRESHOLD,
        silence_duration=SILENCE_DURATION,
        min_speech=MIN_SPEECH_DURATION,
        max_segment=MAX_SEGMENT_DURATION,
        preroll=PREROLL_DURATION,
    ):
        import numpy as np

        self._np = np
        self._sample_rate = sample_rate
        self._silence_threshold = silence_threshold
        self._silence_duration = silence_duration
        self._min_speech = min_speech
        self._max_segment = max_segment
        self._frame_size = max(1, int(sample_rate * FRAME_DURATION))
        self._pending = np.zeros(0, dtype=np.float32)
        self._segment = []
        self._preroll = deque(maxlen=max(1, int(preroll / FRAME_DURATION)))
        self._silence = 0.0
        self._speaking = False
        self._voiced = 0.0
        self._last_voiced = -1

    def push(self, audio):
        """Feed float32 samples, return the utterances they completed."""
        self._pending = self._np.concatenate((self._pending, audio))
        finished = []
        while len(self._pending) >= self._frame_size:
            frame = self._pending[: self._frame_size]
            self._pending = self._pending[self._frame_size :]
            segment = self._push_frame(frame)
            if segment is not None:
                finished.append(segment)
        return finished

    def _push_frame(self, frame):
        rms = float(self._np.sqrt(self._np.mean(self._np.square(frame))))
        voiced = rms >= self._silence_threshold
        if not self._speaking:
            if not voiced:
                self._preroll.append(frame)
                return None
            # Speech starts: the pre-roll becomes the head of the utterance.
            self._speaking = True
            self._segment = list(self._preroll)
            self._preroll.clear()
            self._silence = 0.0
        self._segment.append(frame)
        if voiced:
            self._voiced += FRAME_DURATION
            self._last_voiced = len(self._segment) - 1
            self._silence = 0.0
        else:
            self._silence += FRAME_DURATION
        duration = len(self._segment) * FRAME_DURATION
        if self._silence >= self._silence_duration or duration >= self._max_segment:
            return self._take()
        return None

    def _take(self):
        segment, voiced, last_voiced = self._segment, self._voiced, self._last_voiced
        self._segment = []
        self._speaking = False
        self._silence = 0.0
        self._voiced = 0.0
        self._last_voiced = -1
        # The voiced duration, not the length of the segment: a door slam
        # followed by the silence timeout is long, and whisper hallucinates
        # a whole sentence on it.
        if not segment or voiced < self._min_speech:
            return None
        # The trailing silence is of no use to the model.
        tail = int(TAIL_DURATION / FRAME_DURATION)
        keep = min(len(segment), last_voiced + 1 + tail)
        return self._np.concatenate(segment[:keep])

    def pending_audio(self):
        """The utterance being collected, for the partial results."""
        if not self._speaking or not self._segment:
            return None
        return self._np.concatenate(self._segment)

    def flush(self):
        """Close the utterance being collected, at the end of the dictation."""
        return self._take()


class Transcriber:
    """Wraps a faster-whisper model, reloaded only when the model changes."""

    def __init__(
        self,
        name=DEFAULT_MODEL,
        compute_type=DEFAULT_COMPUTE_TYPE,
        device=DEFAULT_DEVICE,
    ):
        self._name = name
        self._compute_type = compute_type
        self._device = device
        self._model = None

    def configure(self, name=None, compute_type=None, device=None):
        wanted = (
            name or self._name,
            compute_type or self._compute_type,
            device or self._device,
        )
        if wanted != (self._name, self._compute_type, self._device):
            self._name, self._compute_type, self._device = wanted
            # Dropped here, loaded again by the next transcription.
            self._model = None

    def model(self):
        if self._model is None:
            from faster_whisper import WhisperModel

            log(
                f"loading whisper model={self._name} device={self._device} "
                f"compute_type={self._compute_type}"
            )
            self._model = WhisperModel(
                self._name, device=self._device, compute_type=self._compute_type
            )
        return self._model

    def transcribe(self, audio, language=None, prompt=None):
        """Return (text, detected language, confidence) for one utterance."""
        segments, info = self.model().transcribe(
            audio,
            language=language or None,
            initial_prompt=prompt or None,
            beam_size=BEAM_SIZE,
            # The utterance was already cut on silence, but whisper's own VAD
            # also drops the residual noise the energy detector let through.
            vad_filter=True,
            # Each utterance stands on its own: without this whisper repeats
            # the previous sentence when it hears nothing intelligible.
            condition_on_previous_text=False,
        )
        # transcribe() is lazy, the decoding happens while iterating.
        text = "".join(segment.text for segment in segments).strip()
        return text, info.language, info.language_probability


# --- serve mode ------------------------------------------------------------
#
# stdin carries a binary frame stream: one utf-8 JSON line, immediately
# followed by exactly `size` raw bytes when the request declares a size.
# stdout carries one JSON frame per line.
#
# Requests:  {"cmd": "check"}
#            {"cmd": "models"}
#            {"cmd": "start", "id": 1, "model": "small", "language": "fr",
#             "sampleFormat": "int16", "partials": false, "prompt": "..."}
#            {"cmd": "audio", "id": 1, "size": 8000} + 8000 raw bytes
#            {"cmd": "stop", "id": 1}
#            {"cmd": "cancel", "id": 1}
#            {"cmd": "quit"}
# Frames:    {"type": "ready"|"started"|"partial"|"final"|"end"|"error"
#                     |"models"|"check", ...}


class FrameWriter:
    def __init__(self, stream):
        self._stream = stream
        self._lock = threading.Lock()

    def send(self, frame, payload=None):
        if payload is not None:
            frame["size"] = len(payload)
        line = json.dumps(frame, ensure_ascii=False).encode("utf-8") + b"\n"
        with self._lock:
            self._stream.write(line)
            if payload:
                self._stream.write(payload)
            self._stream.flush()


class FrameReader:
    """Reads the JSON lines and the raw payloads mixed on one binary stream."""

    def __init__(self, stream, chunk_size=65536):
        self._stream = stream
        self._chunk_size = chunk_size
        self._buffer = b""

    def _fill(self):
        read = getattr(self._stream, "read1", self._stream.read)
        chunk = read(self._chunk_size)
        if not chunk:
            return False
        self._buffer += chunk
        return True

    def _read_line(self):
        while b"\n" not in self._buffer:
            if not self._fill():
                return None
        line, _, self._buffer = self._buffer.partition(b"\n")
        return line

    def _read_exactly(self, size):
        while len(self._buffer) < size:
            if not self._fill():
                return None
        payload, self._buffer = self._buffer[:size], self._buffer[size:]
        return payload

    def requests(self):
        """Yield (request, payload) until the stream is closed."""
        while True:
            line = self._read_line()
            if line is None:
                return
            line = line.strip()
            if not line:
                continue
            try:
                request = json.loads(line)
            except json.JSONDecodeError as error:
                yield {"cmd": "!malformed", "message": str(error)}, b""
                continue
            payload = b""
            if size := int(request.get("size") or 0):
                payload = self._read_exactly(size)
                if payload is None:
                    return
            yield request, payload


def serve():
    # Take over the real stdout for the frame stream and point fd 1 at stderr,
    # so that a chatty library (ctranslate2, HuggingFace) cannot corrupt the
    # protocol.
    binary_stdout = os.fdopen(os.dup(sys.stdout.fileno()), "wb")
    os.dup2(sys.stderr.fileno(), sys.stdout.fileno())
    sys.stdout = sys.stderr

    out = FrameWriter(binary_stdout)
    transcriber = Transcriber()
    jobs = queue.Queue()
    cancelled = set()
    cancel_lock = threading.Lock()

    def is_cancelled(job_id):
        with cancel_lock:
            return job_id in cancelled

    def worker():
        """Decodes the utterances one after the other, off the reading thread."""
        while True:
            work = jobs.get()
            if work is None:
                return
            job_id = work["id"]
            if is_cancelled(job_id):
                if work["kind"] == "end":
                    out.send({"type": "end", "id": job_id, "cancelled": True})
                    with cancel_lock:
                        cancelled.discard(job_id)
                continue
            if work["kind"] == "end":
                out.send({"type": "end", "id": job_id, "cancelled": False})
                continue
            try:
                text, language, confidence = transcriber.transcribe(
                    work["audio"], work.get("language"), work.get("prompt")
                )
                if not text:
                    # Silence or noise: nothing the engine could insert.
                    continue
                out.send(
                    {
                        "type": work["kind"],
                        "id": job_id,
                        "text": text,
                        "language": language,
                        "confidence": confidence,
                    }
                )
            except Exception as error:  # noqa: BLE001 - report anything to the engine
                out.send(
                    {
                        "type": "error",
                        "id": job_id,
                        "message": f"{type(error).__name__}: {error}",
                    }
                )

    thread = threading.Thread(target=worker, daemon=True)
    thread.start()
    out.send({"type": "ready", **availability()})

    # State of the dictation which is running, if there is one.
    current = None

    for request, payload in FrameReader(sys.stdin.buffer).requests():
        command = request.get("cmd")
        if command == "start":
            transcriber.configure(
                request.get("model"), request.get("computeType"), request.get("device")
            )
            current = {
                "id": request.get("id", 0),
                "language": request.get("language") or None,
                "prompt": request.get("prompt") or None,
                "sampleFormat": request.get("sampleFormat") or "int16",
                "partials": bool(request.get("partials")),
                "endpointer": Endpointer(),
                "sincePartial": 0.0,
            }
            out.send({"type": "started", "id": current["id"]})
        elif command == "audio":
            if current is None or request.get("id", 0) != current["id"]:
                # Audio of a dictation which was stopped or replaced.
                continue
            audio = pcm_to_float(payload, current["sampleFormat"])
            for utterance in current["endpointer"].push(audio):
                current["sincePartial"] = 0.0
                jobs.put(
                    {
                        "kind": "final",
                        "id": current["id"],
                        "audio": utterance,
                        "language": current["language"],
                        "prompt": current["prompt"],
                    }
                )
            if not current["partials"]:
                continue
            current["sincePartial"] += len(audio) / SAMPLE_RATE
            # A partial costs a full decoding, so it is only computed when the
            # model is idle: a final result must never wait behind one.
            if current["sincePartial"] >= PARTIAL_INTERVAL and jobs.empty():
                if (pending := current["endpointer"].pending_audio()) is not None:
                    current["sincePartial"] = 0.0
                    jobs.put(
                        {
                            "kind": "partial",
                            "id": current["id"],
                            "audio": pending,
                            "language": current["language"],
                            "prompt": current["prompt"],
                        }
                    )
        elif command == "stop":
            job_id = request.get("id", 0)
            if current is not None and job_id == current["id"]:
                if (utterance := current["endpointer"].flush()) is not None:
                    jobs.put(
                        {
                            "kind": "final",
                            "id": job_id,
                            "audio": utterance,
                            "language": current["language"],
                            "prompt": current["prompt"],
                        }
                    )
                current = None
            # Queued behind the utterances, so "end" is the last frame of the job.
            jobs.put({"kind": "end", "id": job_id})
        elif command == "cancel":
            job_id = request.get("id", 0)
            with cancel_lock:
                cancelled.add(job_id)
            if current is not None and job_id == current["id"]:
                current = None
            jobs.put({"kind": "end", "id": job_id})
        elif command == "models":
            out.send({"type": "models", "models": model_table()})
        elif command == "check":
            out.send({"type": "check", **availability()})
        elif command == "quit":
            break
        elif command == "!malformed":
            out.send(
                {"type": "error", "message": f"malformed request: {request['message']}"}
            )
        else:
            out.send({"type": "error", "message": f"unknown command: {command!r}"})

    jobs.put(None)
    thread.join(timeout=5)


# --- one-shot modes --------------------------------------------------------


def read_wav(path):
    """Read a mono 16 bit wav, the format QAudioSource is configured with."""
    with wave.open(path, "rb") as handle:
        if handle.getnchannels() != CHANNELS or handle.getsampwidth() != 2:
            raise ValueError("only mono 16 bit wav files are supported")
        if handle.getframerate() != SAMPLE_RATE:
            raise ValueError(f"expected {SAMPLE_RATE} Hz, got {handle.getframerate()}")
        return pcm_to_float(handle.readframes(handle.getnframes()))


def transcribe(args):
    transcriber = Transcriber(args.model, args.compute_type, args.device)
    text, language, confidence = transcriber.transcribe(
        read_wav(args.file), args.language, args.prompt
    )
    log(f"language={language} confidence={confidence:.2f}")
    print(text)


def main():
    parser = argparse.ArgumentParser(description="Whisper speech-to-text helper")
    subparsers = parser.add_subparsers(dest="command", required=True)

    subparsers.add_parser("check", help="report whether whisper is usable")
    subparsers.add_parser("models", help="list the models, as json")
    subparsers.add_parser("serve", help="frame protocol on stdin/stdout")

    fetch = subparsers.add_parser("download", help="download a model, as json")
    fetch.add_argument("--model", default=DEFAULT_MODEL)
    fetch.add_argument(
        "--dry-run", action="store_true", help="only report whether it is missing"
    )
    fetch.add_argument(
        "--force", action="store_true", help="download it again even when cached"
    )
    fetch.add_argument(
        "--all",
        action="store_true",
        help="report the state of every model instead of downloading one",
    )

    one_shot = subparsers.add_parser("transcribe", help="transcribe a wav file")
    one_shot.add_argument("--file", required=True)
    one_shot.add_argument("--model", default=DEFAULT_MODEL)
    one_shot.add_argument("--language", default=None)
    one_shot.add_argument("--prompt", default=None)
    one_shot.add_argument(
        "--compute-type", dest="compute_type", default=DEFAULT_COMPUTE_TYPE
    )
    one_shot.add_argument("--device", default=DEFAULT_DEVICE)

    args = parser.parse_args()
    if args.command == "check":
        report = availability()
        print(json.dumps(report, ensure_ascii=False))
        # Non zero so that a plain shell check works too.
        return 0 if report["available"] else 1
    if args.command == "models":
        print(json.dumps({"models": model_table()}, ensure_ascii=False))
        return 0
    if args.command == "serve":
        serve()
        return 0
    if args.command == "download":
        return download(args)
    transcribe(args)
    return 0


if __name__ == "__main__":
    sys.exit(main())
