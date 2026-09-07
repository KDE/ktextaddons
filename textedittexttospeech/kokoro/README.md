# Kokoro plugins

## Opensuse

Install python3, numpy, SoundFile, libespeak-ng1, aplay, paplay, pw-play
sudo zypper install espeak-ng python311-torch

It seems that it doesn't work with python3.13

```bash
rm -rf ~/.venv/kokoro
python3.11 -m venv ~/.venv/kokoro
~/.venv/kokoro/bin/pip install
--index-url https://download.pytorch.org/whl/cpu torch
~/.venv/kokoro/bin/pip install kokoro
```
