# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_library(KokoroTextToSpeechPlugin)

target_sources(
    KokoroTextToSpeechPlugin
    PRIVATE
        texttospeechkokoroengine.h
        texttospeechkokoroengine.cpp
        texttospeechkokoro.h
        texttospeechkokoro.cpp
)

target_link_libraries(KokoroTextToSpeechPlugin PUBLIC Qt::TextToSpeech)
