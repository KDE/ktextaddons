# SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_library(KokoroTextToSpeechPlugin)

ecm_qt_declare_logging_category(KokoroTextToSpeechPlugin
    HEADER texttospeech_kokoro_debug.h
    IDENTIFIER KOKORO_TEXT_TO_SPEECH_PLUGIN_LOG
    CATEGORY_NAME org.kde.kf.textospeech.kokoro
    DESCRIPTION "kokoro text to speech plugin"
    EXPORT KTEXTADDONS
)

target_sources(
    KokoroTextToSpeechPlugin
    PRIVATE
        texttospeechkokoroengine.h
        texttospeechkokoroengine.cpp
        texttospeechkokoro.h
        texttospeechkokoro.cpp
        texttospeechkokoroplugin.h
        texttospeechkokoroplugin.cpp
        texttospeechkokoroutils.h
        texttospeechkokoroutils.cpp
)

target_link_libraries(KokoroTextToSpeechPlugin PUBLIC Qt::TextToSpeech)
install(TARGETS KokoroTextToSpeechPlugin DESTINATION ${KDE_INSTALL_PLUGINDIR}/texttospeech/)
