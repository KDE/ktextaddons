# SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

# QAudioSink plays what the backend synthesizes. QtMultimedia is only looked up
# at the end of the top level CMakeLists.txt, after this directory.
find_package(Qt6 ${QT_REQUIRED_VERSION} CONFIG REQUIRED Multimedia)

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
        texttospeechkokoro.h
        texttospeechkokoro.cpp
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

# The headers are not installed: the sources of this repository which link
# against it include them from the build tree.
target_include_directories(
    kokorotexttospeech
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

target_link_libraries(
    kokorotexttospeech
    PUBLIC
        kokoroinstalltexttospeech
        Qt::TextToSpeech
        Qt::Multimedia
    PRIVATE
        KF6::I18n
)

set_target_properties(
    kokorotexttospeech
    PROPERTIES
        VERSION
            ${TEXTEDITTEXTTOSPEECH_VERSION}
        SOVERSION
            ${TEXTEDITTEXTTOSPEECH_SOVERSION}
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
        texttospeechkokoroplugin.h
        texttospeechkokoroplugin.cpp
)

target_link_libraries(
    KokoroTextToSpeechPlugin
    PUBLIC
        kokorotexttospeech
        KF6::I18n
)
install(TARGETS KokoroTextToSpeechPlugin DESTINATION ${KDE_INSTALL_PLUGINDIR}/texttospeech/)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
