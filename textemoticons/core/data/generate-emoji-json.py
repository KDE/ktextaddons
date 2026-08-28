#!/usr/bin/env python3
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
"""Regenerate textemoticons/core/data/emoji.json from emojibase.

The emoji set used to come from joypixels/emoji-toolkit (formerly EmojiOne),
which stopped being a usable source of truth: its last snapshot here covered
Unicode 15.1 only, and Rocket.Chat moved to emojibase shortcodes, so the names
it sends for reactions no longer matched ours.

emojibase is now the source of truth for the emoji set, the categories, the
sort order and the primary ``shortname``. Every name we used to ship stays
available as an alias, so old shortnames typed by users or stored in messages
keep resolving: ``UnicodeEmoticonParser`` loads ``shortname_alternates`` and
``ascii`` as aliases and ``UnicodeEmoticon::hasEmoji()`` matches the
identifier, the unicode string and every alias.

Only the fields ``UnicodeEmoticonParser`` reads are emitted.

Usage:
    ./generate-emoji-json.py                  # download emojibase, rewrite emoji.json in place
    ./generate-emoji-json.py --emojibase DIR  # use a local emojibase-data checkout instead
"""

import argparse
import json
import pathlib
import sys
import urllib.request

DATA_URL = "https://cdn.jsdelivr.net/npm/emojibase-data@latest/en/data.json"
SHORTCODES_URL = (
    "https://cdn.jsdelivr.net/npm/emojibase-data@latest/en/shortcodes/emojibase.json"
)

# emojibase groups -> the categories UnicodeEmoticonManager knows about.
# Group 2 (components) and the ungrouped regional indicators are special-cased below.
GROUP_TO_CATEGORY = {
    0: "people",  # smileys & emotion
    1: "people",  # people & body
    3: "nature",  # animals & nature
    4: "food",  # food & drink
    5: "travel",  # travel & places
    6: "activity",  # activities
    7: "objects",  # objects
    8: "symbols",  # symbols
    9: "flags",  # flags
}

# The five skin tone modifiers; the rest of group 2 is hair components, which
# belong with the people they modify.
TONE_MODIFIERS = {"1F3FB", "1F3FC", "1F3FD", "1F3FE", "1F3FF"}


def hex_from_emoji(text):
    """Codepoints of an emoji as the hyphen separated hex string the parser expects.

    Padded to four digits like emojibase hexcodes, so that keycaps and the
    handful of latin-1 emojis keep matching our previous entries.
    """
    return "-".join(f"{ord(char):04x}" for char in text)


def unqualify(codepoints):
    """Key used to match our old entries against emojibase, ignoring VS16."""
    return "-".join(part for part in codepoints.lower().split("-") if part != "fe0f")


def load_json(path_or_url):
    if path_or_url.startswith("https://"):
        with urllib.request.urlopen(path_or_url) as response:  # noqa: S310
            return json.load(response)
    return json.loads(pathlib.Path(path_or_url).read_text(encoding="utf-8"))


def load_legacy_names(path):
    """Collect the shortnames and ascii aliases we used to ship, by codepoints."""
    if not path.exists():
        return {}
    legacy = {}
    for key, value in json.loads(path.read_text(encoding="utf-8")).items():
        codepoints = value.get("code_points", {}).get("fully_qualified") or key
        entry = legacy.setdefault(unqualify(codepoints), {"names": [], "ascii": []})
        for name in [value.get("shortname")] + list(
            value.get("shortname_alternates") or []
        ):
            if name and name not in entry["names"]:
                entry["names"].append(name)
        for ascii_alias in value.get("ascii") or []:
            if ascii_alias not in entry["ascii"]:
                entry["ascii"].append(ascii_alias)
    return legacy


def category_of(record):
    if record.get("group") is None:
        # Regional indicator symbols, which have no CLDR group.
        return "regional"
    if record["group"] == 2:
        return "modifier" if record["hexcode"] in TONE_MODIFIERS else "people"
    return GROUP_TO_CATEGORY.get(record["group"])


def shortcodes_of(shortcodes, hexcode):
    codes = shortcodes.get(hexcode)
    if not codes:
        return []
    return codes if isinstance(codes, list) else [codes]


def tone_suffix(tone):
    tones = tone if isinstance(tone, list) else [tone]
    return "_tone" + "-".join(str(value) for value in tones)


def build_entries(data, shortcodes):
    """One entry per emoji and per skin tone variant, in emojibase order."""
    entries = []
    for record in data:
        category = category_of(record)
        if category is None:
            continue
        codes = shortcodes_of(shortcodes, record["hexcode"])
        if not codes:
            continue
        skins = [skin for skin in record.get("skins") or [] if skin.get("tone")]
        entries.append(
            {
                "key": record["hexcode"].lower(),
                "unicode": record["emoji"],
                "name": record.get("label"),
                "unicode_version": record.get("version"),
                "category": category,
                "order": record.get("order"),
                "primary": f":{codes[0]}:",
                "alternates": [f":{code}:" for code in codes[1:]],
                "diversity_children": [skin["hexcode"].lower() for skin in skins],
            }
        )
        for skin in skins:
            # emojibase names a skin tone variant after the base plus a _toneN suffix,
            # which is the convention EmojiSortFilterProxyModel filters tones on.
            suffix = tone_suffix(skin["tone"])
            skin_codes = shortcodes_of(shortcodes, skin["hexcode"]) or [
                f"{codes[0]}{suffix}"
            ]
            entries.append(
                {
                    "key": skin["hexcode"].lower(),
                    "unicode": skin["emoji"],
                    "name": skin.get("label"),
                    "unicode_version": skin.get("version"),
                    "category": category,
                    "order": skin.get("order"),
                    "primary": f":{skin_codes[0]}:",
                    # The base alternates only exist unsuffixed, so suffix them here.
                    "alternates": [f":{code}:" for code in skin_codes[1:]]
                    + [f":{code}{suffix}:" for code in codes[1:]],
                    "diversity_children": [],
                }
            )
    return entries


def assign_names(entries, legacy):
    """Give every name a single owner.

    ``UnicodeEmoticonManager::unicodeEmoticonForEmoji()`` returns the first
    emoji claiming a name, so a name shared by two entries would resolve to
    whichever sorts first. Primary names win, then emojibase alternates, then
    the names we used to ship.
    """
    owner = {}
    for entry in entries:
        clash = owner.get(entry["primary"])
        if clash is not None:
            print(
                f"warning: {entry['primary']} is the primary name of both "
                f"{clash['key']} and {entry['key']}, keeping {clash['key']}",
                file=sys.stderr,
            )
            continue
        owner[entry["primary"]] = entry

    dropped = 0
    for entry in entries:
        aliases = []
        candidates = list(entry["alternates"])
        candidates += legacy.get(unqualify(hex_from_emoji(entry["unicode"])), {}).get(
            "names", []
        )
        candidates += legacy.get(unqualify(entry["key"]), {}).get("names", [])
        for name in candidates:
            if name == entry["primary"] or name in aliases:
                continue
            if name in owner:
                dropped += 1
                continue
            owner[name] = entry
            aliases.append(name)
        entry["aliases"] = aliases
    return dropped


def assign_orders(entries):
    """Keep the emojibase order; the ungrouped ones go last."""
    known = [entry["order"] for entry in entries if entry["order"] is not None]
    next_order = max(known) + 1 if known else 1
    for entry in entries:
        if entry["order"] is None:
            entry["order"] = next_order
            next_order += 1


def to_json(entries, legacy):
    result = {}
    for entry in entries:
        if entry["key"] in result:
            print(
                f"warning: duplicated key {entry['key']}, keeping the first one",
                file=sys.stderr,
            )
            continue
        codepoints = hex_from_emoji(entry["unicode"])
        result[entry["key"]] = {
            "name": entry["name"],
            "unicode_version": entry["unicode_version"],
            "category": entry["category"],
            "order": entry["order"],
            "shortname": entry["primary"],
            "shortname_alternates": entry["aliases"],
            "ascii": legacy.get(unqualify(codepoints), {}).get("ascii", []),
            "diversity_children": entry["diversity_children"],
            "code_points": {"base": entry["key"], "fully_qualified": codepoints},
        }
    return result


def main():
    here = pathlib.Path(__file__).resolve().parent
    parser = argparse.ArgumentParser(description=__doc__)
    parser.add_argument(
        "--emojibase",
        metavar="DIR",
        help="local emojibase-data directory, containing en/data.json; downloaded when omitted",
    )
    parser.add_argument(
        "--legacy",
        metavar="FILE",
        type=pathlib.Path,
        default=here / "emoji.json",
        help="emoji.json to harvest the previous shortnames from (default: %(default)s)",
    )
    parser.add_argument(
        "-o",
        "--output",
        metavar="FILE",
        type=pathlib.Path,
        default=here / "emoji.json",
        help="where to write the generated file (default: %(default)s)",
    )
    options = parser.parse_args()

    if options.emojibase:
        base = pathlib.Path(options.emojibase)
        data_source = str(base / "en" / "data.json")
        shortcodes_source = str(base / "en" / "shortcodes" / "emojibase.json")
    else:
        data_source, shortcodes_source = DATA_URL, SHORTCODES_URL

    data = load_json(data_source)
    shortcodes = load_json(shortcodes_source)
    legacy = load_legacy_names(options.legacy)

    entries = build_entries(data, shortcodes)
    dropped = assign_names(entries, legacy)
    assign_orders(entries)
    result = to_json(entries, legacy)

    options.output.write_text(
        json.dumps(result, indent=4, ensure_ascii=False) + "\n", encoding="utf-8"
    )

    names = sum(1 + len(value["shortname_alternates"]) for value in result.values())
    print(
        f"{options.output}: {len(result)} emojis, {names} names ({dropped} ambiguous legacy names dropped)"
    )


if __name__ == "__main__":
    main()
