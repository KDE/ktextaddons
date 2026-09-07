# SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_library(kokorotexttospeech)
ecm_qt_declare_logging_category(kokorotexttospeech
    HEADER texttospeech_kokoro_lib_debug.h
    IDENTIFIER KOKORO_TEXT_TO_SPEECH_LIB_LOG
    CATEGORY_NAME org.kde.kf.textospeech_lib.kokoro
    DESCRIPTION "kokoro text to speech lib"
    EXPORT KTEXTADDONS
)

target_sources(
    kokorotexttospeech
    PRIVATE
        texttospeechkokoroutils.h
        texttospeechkokoroutils.cpp
        texttospeechkokoroinstallpythondialog.h
        texttospeechkokoroinstallpythondialog.cpp
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        kokorotexttospeech
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
generate_export_header(kokorotexttospeech BASE_NAME kokorotexttospeech)

target_link_libraries(
    kokorotexttospeech
    PUBLIC
        Qt::TextToSpeech
        Qt::Widgets
)

set_target_properties(
    kokorotexttospeech
    PROPERTIES
        VERSION
            ${TEXTEDITTEXTTOSPEECH_VERSION}
        SOVERSION
            ${TEXTEDITTEXTTOSPEECH_VERSION}
        EXPORT_NAME
            kokorotexttospeech
)

install(
    TARGETS
        kokorotexttospeech
        ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    LIBRARY
        NAMELINK_SKIP
)

####

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
)

target_link_libraries(KokoroTextToSpeechPlugin PUBLIC kokorotexttospeech)
install(TARGETS KokoroTextToSpeechPlugin DESTINATION ${KDE_INSTALL_PLUGINDIR}/texttospeech/)

install(PROGRAMS scripts/kokoro_helper.py DESTINATION ${KDE_INSTALL_BINDIR})

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
