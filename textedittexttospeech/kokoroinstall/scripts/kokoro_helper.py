#!/usr/bin/env python3
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: LGPL-2.0-or-later
"""Kokoro text-to-speech helper.

Standalone test tool and, in ``serve`` mode, the backend process driven over a
pipe by the Qt TextToSpeechKokoroEngine plugin.

Requires ``pip install kokoro`` (pulls in PyTorch and misaki) plus espeak-ng
installed system wide. The model itself (~330 MB) and the voices (512 kB each)
are fetched from HuggingFace and cached in ~/.cache/huggingface: on first use
by ``say``/``serve``, or upfront with ``download``.

Examples:
    kokoro_helper.py check
    kokoro_helper.py voices
    kokoro_helper.py download                # model + the 54 voices
    kokoro_helper.py download model          # only the model
    kokoro_helper.py download fr_FR ff_siwis # a whole language, or one voice
    kokoro_helper.py download --dry-run all  # report what is missing
    kokoro_helper.py say --text "Bonjour le monde" --voice ff_siwis --play
    kokoro_helper.py say --text "Hello there" --out /tmp/hello.wav
    kokoro_helper.py serve      # newline-delimited JSON on stdin, frames on stdout
"""

import argparse
import importlib.util
import json
import os
import queue
import shutil
import subprocess
import sys
import threading
import wave

SAMPLE_RATE = 24000
CHANNELS = 1
DEFAULT_REPO_ID = "hexgrad/Kokoro-82M"

# What ``download`` has to fetch for the model itself. kokoro keeps the same
# table in KModel.MODEL_NAMES, duplicated here so that downloading a file does
# not have to import kokoro, and through it torch.
MODEL_FILES = {
    "hexgrad/Kokoro-82M": "kokoro-v1_0.pth",
    "hexgrad/Kokoro-82M-v1.1-zh": "kokoro-v1_1-zh.pth",
}

# Kokoro voice ids encode the language in the first character and the gender in
# the second one, so the whole voice table is derived from the id list.
LANGUAGES = {
    "a": ("en_US", "American English"),
    "b": ("en_GB", "British English"),
    "e": ("es_ES", "Spanish"),
    "f": ("fr_FR", "French"),
    "h": ("hi_IN", "Hindi"),
    "i": ("it_IT", "Italian"),
    "p": ("pt_BR", "Brazilian Portuguese"),
    "j": ("ja_JP", "Japanese"),
    "z": ("zh_CN", "Mandarin Chinese"),
}

# Japanese and Chinese need a dedicated G2P (misaki[ja] / misaki[zh]) that
# espeak-ng cannot provide, so they are reported but flagged as extra.
EXTRA_G2P_LANGUAGES = ("j", "z")

VOICE_IDS = (
    "af_heart",
    "af_alloy",
    "af_aoede",
    "af_bella",
    "af_jessica",
    "af_kore",
    "af_nicole",
    "af_nova",
    "af_river",
    "af_sarah",
    "af_sky",
    "am_adam",
    "am_echo",
    "am_eric",
    "am_fenrir",
    "am_liam",
    "am_michael",
    "am_onyx",
    "am_puck",
    "am_santa",
    "bf_alice",
    "bf_emma",
    "bf_isabella",
    "bf_lily",
    "bm_daniel",
    "bm_fable",
    "bm_george",
    "bm_lewis",
    "ef_dora",
    "em_alex",
    "em_santa",
    "ff_siwis",
    "hf_alpha",
    "hf_beta",
    "hm_omega",
    "hm_psi",
    "if_sara",
    "im_nicola",
    "pf_dora",
    "pm_alex",
    "pm_santa",
    "jf_alpha",
    "jf_gongitsune",
    "jf_nezumi",
    "jf_tebukuro",
    "jm_kumo",
    "zf_xiaobei",
    "zf_xiaoni",
    "zf_xiaoxiao",
    "zf_xiaoyi",
    "zm_yunjian",
    "zm_yunxi",
    "zm_yunxia",
    "zm_yunyang",
)


def voice_table():
    voices = []
    for voice_id in VOICE_IDS:
        lang_code = voice_id[0]
        locale, language = LANGUAGES[lang_code]
        voices.append(
            {
                "id": voice_id,
                "name": voice_id.split("_", 1)[1].capitalize(),
                "langCode": lang_code,
                "locale": locale,
                "language": language,
                "gender": "female" if voice_id[1] == "f" else "male",
                "needsExtraG2p": lang_code in EXTRA_G2P_LANGUAGES,
            }
        )
    return voices


def log(*args):
    print(*args, file=sys.stderr, flush=True)


def availability():
    """Report what is installed without importing the heavy libraries."""
    missing = [
        name for name in ("kokoro", "torch") if not importlib.util.find_spec(name)
    ]
    espeak = shutil.which("espeak-ng") or shutil.which("espeak")
    return {
        "available": not missing and espeak is not None,
        "missing": missing,
        "espeakNg": espeak,
        "python": sys.executable,
    }


def to_pcm(audio, sample_format):
    """Convert one Kokoro output chunk to little-endian PCM bytes."""
    import numpy as np

    if hasattr(audio, "detach"):  # torch.Tensor
        audio = audio.detach().cpu().numpy()
    audio = np.asarray(audio, dtype=np.float32).reshape(-1)
    if sample_format == "float":
        return audio.astype("<f4").tobytes()
    return (np.clip(audio, -1.0, 1.0) * 32767.0).astype("<i2").tobytes()


class Synthesizer:
    """Wraps a KPipeline, rebuilt only when the language changes."""

    def __init__(self, repo_id=DEFAULT_REPO_ID):
        self._repo_id = repo_id
        self._pipeline = None
        self._lang_code = None

    def pipeline(self, lang_code):
        if self._pipeline is None or self._lang_code != lang_code:
            import kokoro

            log(f"loading KPipeline lang_code={lang_code} repo_id={self._repo_id}")
            self._pipeline = kokoro.KPipeline(
                lang_code=lang_code, repo_id=self._repo_id
            )
            self._lang_code = lang_code
        return self._pipeline

    def chunks(self, text, voice, speed=1.0, split_pattern=r"\n+"):
        """Yield (graphemes, phonemes, audio) as soon as each chunk is ready."""
        pipeline = self.pipeline(voice[0])
        for graphemes, phonemes, audio in pipeline(
            text, voice=voice, speed=speed, split_pattern=split_pattern
        ):
            if audio is not None:
                yield graphemes, phonemes, audio


# --- serve mode ------------------------------------------------------------
#
# stdout carries a binary frame stream: one utf-8 JSON line, immediately
# followed by exactly `size` raw bytes when the frame declares a size.
# stdin carries one JSON request per line.
#
# Requests:  {"cmd": "check"}
#            {"cmd": "voices"}
#            {"cmd": "say", "id": 1, "text": "...", "voice": "af_heart",
#             "speed": 1.0, "sampleFormat": "int16"}
#            {"cmd": "cancel", "id": 1}
#            {"cmd": "quit"}
# Frames:    {"type": "ready"|"format"|"chunk"|"end"|"error"|"voices"|"check", ...}


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


def serve(repo_id=DEFAULT_REPO_ID):
    # Take over the real stdout for the frame stream and point fd 1 at stderr,
    # so that a chatty library (torch, HuggingFace) cannot corrupt the protocol.
    binary_stdout = os.fdopen(os.dup(sys.stdout.fileno()), "wb")
    os.dup2(sys.stderr.fileno(), sys.stdout.fileno())
    sys.stdout = sys.stderr

    out = FrameWriter(binary_stdout)
    synthesizer = Synthesizer(repo_id)
    jobs = queue.Queue()
    cancelled = set()
    cancel_lock = threading.Lock()

    def is_cancelled(job_id):
        with cancel_lock:
            return job_id in cancelled

    def worker():
        while True:
            request = jobs.get()
            if request is None:
                return
            job_id = request.get("id", 0)
            if is_cancelled(job_id):
                out.send({"type": "end", "id": job_id, "cancelled": True})
                continue
            voice = request.get("voice") or "af_heart"
            sample_format = request.get("sampleFormat") or "int16"
            try:
                index = 0
                for graphemes, phonemes, audio in synthesizer.chunks(
                    request.get("text", ""),
                    voice,
                    float(request.get("speed", 1.0)),
                    request.get("splitPattern", r"\n+"),
                ):
                    if is_cancelled(job_id):
                        break
                    if index == 0:
                        # Announced only once the model actually produced audio,
                        # so that the engine does not open an audio sink for a
                        # synthesis that ends up failing.
                        out.send(
                            {
                                "type": "format",
                                "id": job_id,
                                "sampleRate": SAMPLE_RATE,
                                "channels": CHANNELS,
                                "sampleFormat": sample_format,
                            }
                        )
                    out.send(
                        {
                            "type": "chunk",
                            "id": job_id,
                            "index": index,
                            "text": graphemes,
                            "phonemes": phonemes,
                        },
                        to_pcm(audio, sample_format),
                    )
                    index += 1
                out.send(
                    {"type": "end", "id": job_id, "cancelled": is_cancelled(job_id)}
                )
            except Exception as error:  # noqa: BLE001 - report anything to the engine
                out.send(
                    {
                        "type": "error",
                        "id": job_id,
                        "message": f"{type(error).__name__}: {error}",
                    }
                )
            finally:
                with cancel_lock:
                    cancelled.discard(job_id)

    thread = threading.Thread(target=worker, daemon=True)
    thread.start()
    out.send({"type": "ready", **availability()})

    for line in sys.stdin:
        line = line.strip()
        if not line:
            continue
        try:
            request = json.loads(line)
        except json.JSONDecodeError as error:
            out.send({"type": "error", "message": f"malformed request: {error}"})
            continue
        command = request.get("cmd")
        if command == "say":
            jobs.put(request)
        elif command == "cancel":
            with cancel_lock:
                cancelled.add(request.get("id", 0))
        elif command == "voices":
            out.send({"type": "voices", "voices": voice_table()})
        elif command == "check":
            out.send({"type": "check", **availability()})
        elif command == "quit":
            break
        else:
            out.send({"type": "error", "message": f"unknown command: {command!r}"})

    jobs.put(None)
    thread.join(timeout=5)


# --- download mode ---------------------------------------------------------


def selector_table():
    """Every voice selector accepted by ``download`` -> the voice ids it means."""
    table = {"voices": list(VOICE_IDS)}
    shorts = {}
    for code, (locale, _) in LANGUAGES.items():
        voice_ids = [voice_id for voice_id in VOICE_IDS if voice_id[0] == code]
        table[code] = voice_ids
        table[locale.lower()] = voice_ids
        shorts.setdefault(locale.split("_")[0].lower(), []).append(code)
    # "fr" stands for fr_FR, but "en" would be ambiguous (en_US and en_GB), so
    # only the short forms naming a single language are accepted.
    for short, codes in shorts.items():
        if len(codes) == 1:
            table[short] = table[codes[0]]
    table.update({voice_id: [voice_id] for voice_id in VOICE_IDS})
    return table


def resolve_selectors(selectors):
    """Turn the ``download`` selectors into (model wanted, voice ids).

    A selector is "all", "model", "voices", a language code ("f"), a locale
    ("fr" or "fr_FR") or a voice id ("ff_siwis"). Unknown ones raise ValueError.
    """
    table = selector_table()
    want_model = False
    voices = []
    for selector in selectors or ("all",):
        key = selector.lower()
        if key == "all":
            want_model = True
            matches = VOICE_IDS
        elif key == "model":
            want_model = True
            matches = ()
        elif key in table:
            matches = table[key]
        else:
            raise ValueError(
                f"unknown selector {selector!r}: expected all, model, voices, a "
                "language code or locale (f, fr, fr_FR) or a voice id (ff_siwis)"
            )
        for voice_id in matches:
            # A voice named twice, directly and through its language, is fetched once.
            if voice_id not in voices:
                voices.append(voice_id)
    return want_model, voices


def download(args):
    """Fetch the requested files into the HuggingFace cache, skipping what is there."""
    try:
        want_model, voices = resolve_selectors(args.what)
    except ValueError as error:
        log(error)
        return 2

    from huggingface_hub import hf_hub_download, try_to_load_from_cache

    if args.json:
        # The download bars land on stderr, which is only noise for a caller
        # that follows the json events.
        from huggingface_hub.utils import disable_progress_bars

        disable_progress_bars()

    files = []
    if want_model:
        model_file = MODEL_FILES.get(args.repo_id)
        if model_file is None:
            log(f"unknown repository {args.repo_id!r}: no model file to download")
            return 2
        # config.json is what KModel reads before the weights themselves.
        files += [("model", "config.json"), ("model", model_file)]
    files += [("voice", f"voices/{voice_id}.pt") for voice_id in voices]

    def report(**event):
        if args.json:
            print(json.dumps(event, ensure_ascii=False), flush=True)
            return
        if event["type"] == "finished":
            log(f"finished: {event['total']} file(s), {event['failed']} failure(s)")
            return
        detail = event.get("message") or event.get("path") or ""
        log(
            f"[{event['index']}/{event['total']}] {event['type']}: {event['file']} {detail}".rstrip()
        )

    failures = 0
    for index, (kind, filename) in enumerate(files, start=1):
        where = try_to_load_from_cache(args.repo_id, filename)
        # try_to_load_from_cache returns a sentinel, not a path, for a file the
        # cache knows to be missing on the hub.
        cached = where if isinstance(where, str) else None
        progress = {"kind": kind, "file": filename, "index": index, "total": len(files)}
        if cached and not args.force:
            report(type="cached", path=cached, **progress)
            continue
        if args.dry_run:
            report(type="missing", **progress)
            continue
        report(type="downloading", **progress)
        try:
            path = hf_hub_download(
                repo_id=args.repo_id, filename=filename, force_download=args.force
            )
        except Exception as error:  # noqa: BLE001 - network, disk, offline mode...
            failures += 1
            report(type="error", message=f"{type(error).__name__}: {error}", **progress)
            continue
        report(type="done", path=path, **progress)
    report(type="finished", total=len(files), failed=failures)
    return 1 if failures else 0


# --- one-shot modes --------------------------------------------------------


def write_wav(path, pcm_chunks):
    with wave.open(path, "wb") as handle:
        handle.setnchannels(CHANNELS)
        handle.setsampwidth(2)
        handle.setframerate(SAMPLE_RATE)
        for chunk in pcm_chunks:
            handle.writeframes(chunk)


def play(pcm_chunks):
    """Play int16 PCM, preferring sounddevice and falling back to aplay."""
    if importlib.util.find_spec("sounddevice") and importlib.util.find_spec("numpy"):
        import numpy as np
        import sounddevice

        for chunk in pcm_chunks:
            sounddevice.play(np.frombuffer(chunk, dtype="<i2"), samplerate=SAMPLE_RATE)
            sounddevice.wait()
        return
    player = shutil.which("aplay") or shutil.which("paplay")
    if not player:
        log("no sounddevice, aplay or paplay available; use --out instead")
        return 1
    args = (
        [player, "-f", "S16_LE", "-r", str(SAMPLE_RATE), "-c", str(CHANNELS), "-q", "-"]
        if player.endswith("aplay")
        else [
            player,
            "--raw",
            f"--rate={SAMPLE_RATE}",
            "--format=s16le",
            f"--channels={CHANNELS}",
        ]
    )
    process = subprocess.Popen(args, stdin=subprocess.PIPE)
    for chunk in pcm_chunks:
        process.stdin.write(chunk)
    process.stdin.close()
    return process.wait()


def say(args):
    text = args.text
    if text == "-":
        text = sys.stdin.read()
    if not text.strip():
        log("nothing to say")
        return 1
    synthesizer = Synthesizer(args.repo_id)
    chunks = []
    for graphemes, phonemes, audio in synthesizer.chunks(text, args.voice, args.speed):
        log(f"chunk: {graphemes!r}\n  phonemes: {phonemes}")
        chunks.append(to_pcm(audio, "int16"))
    if not chunks:
        log("Kokoro produced no audio")
        return 1
    frames = sum(len(chunk) for chunk in chunks) // 2
    log(f"{len(chunks)} chunk(s), {frames / SAMPLE_RATE:.2f}s")
    if args.out:
        write_wav(args.out, chunks)
        log(f"written {args.out}")
    if args.play or not args.out:
        return play(chunks) or 0
    return 0


def main():
    parser = argparse.ArgumentParser(
        description=__doc__, formatter_class=argparse.RawDescriptionHelpFormatter
    )
    parser.add_argument(
        "--repo-id", default=DEFAULT_REPO_ID, help="HuggingFace repository of the model"
    )
    commands = parser.add_subparsers(dest="command", required=True)

    commands.add_parser("check", help="report whether the Kokoro backend is usable")
    commands.add_parser("voices", help="list the known voices as JSON")
    commands.add_parser("serve", help="run the JSON/PCM protocol used by the Qt plugin")

    download_parser = commands.add_parser(
        "download",
        help="fetch the model and the voices upfront, instead of on first use",
        description="Selectors: all (the default), model, voices, a language "
        "code (f), a locale (fr, fr_FR) or a voice id (ff_siwis).",
    )
    download_parser.add_argument(
        "what", nargs="*", metavar="SELECTOR", help="what to download, all by default"
    )
    download_parser.add_argument(
        "--dry-run", action="store_true", help="only report what is missing"
    )
    download_parser.add_argument(
        "--force", action="store_true", help="download again even when cached"
    )
    download_parser.add_argument(
        "--json", action="store_true", help="report one json event per line on stdout"
    )

    say_parser = commands.add_parser(
        "say", help="synthesize one text and play it or save it"
    )
    say_parser.add_argument(
        "--text", required=True, help="text to speak, or - to read stdin"
    )
    say_parser.add_argument(
        "--voice", default="af_heart", choices=VOICE_IDS, metavar="VOICE"
    )
    say_parser.add_argument("--speed", type=float, default=1.0)
    say_parser.add_argument("--out", help="write a 24 kHz mono wav file here")
    say_parser.add_argument(
        "--play", action="store_true", help="play even when --out is given"
    )

    args = parser.parse_args()
    if args.command == "check":
        state = availability()
        print(json.dumps(state, indent=2))
        if not state["available"]:
            if state["missing"]:
                log(
                    "missing python modules: "
                    + ", ".join(state["missing"])
                    + " -> pip install kokoro"
                )
            if not state["espeakNg"]:
                log("espeak-ng not found -> install the espeak-ng package")
        return 0 if state["available"] else 1
    if args.command == "voices":
        print(json.dumps(voice_table(), indent=2, ensure_ascii=False))
        return 0
    if args.command == "serve":
        serve(args.repo_id)
        return 0
    if args.command == "download":
        return download(args)
    return say(args)


if __name__ == "__main__":
    sys.exit(main())
