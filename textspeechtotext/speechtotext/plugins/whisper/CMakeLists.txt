# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

add_library(speechtotextwhisper)
ecm_qt_declare_logging_category(speechtotextwhisper
    HEADER speechtotextwhisper_lib_debug.h
    IDENTIFIER SPEECHTOTEXT_WHISPER_LIB_LOG
    CATEGORY_NAME org.kde.kf.speechtotext_lib.whisper
    DESCRIPTION "whisper speech to text lib"
    EXPORT KTEXTADDONS
)

target_sources(
    speechtotextwhisper
    PRIVATE
        whisperspeechtotextpluginjob.h
        whisperspeechtotextpluginjob.cpp
        whisperspeechtotextutils.h
        whisperspeechtotextutils.cpp
        whisperspeechtotextcheckjob.h
        whisperspeechtotextcheckjob.cpp
        whisperspeechtotextinstalljob.h
        whisperspeechtotextinstalljob.cpp
        whisperspeechtotextinstallpythonwidget.h
        whisperspeechtotextinstallpythonwidget.cpp
        whisperspeechtotextinstallpythondialog.h
        whisperspeechtotextinstallpythondialog.cpp
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        speechtotextwhisper
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
generate_export_header(speechtotextwhisper BASE_NAME speechtotextwhisper)

target_include_directories(
    speechtotextwhisper
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

target_link_libraries(
    speechtotextwhisper
    PRIVATE
        Qt::Widgets
        KF6::I18n
        KF6::WidgetsAddons
        KF6::TextAddonsWidgets
)

set_target_properties(
    speechtotextwhisper
    PROPERTIES
        VERSION
            ${TEXTSPEECHTOTEXT_VERSION}
        SOVERSION
            ${TEXTSPEECHTOTEXT_SOVERSION}
        EXPORT_NAME
            speechtotextwhisper
)

install(
    TARGETS
        speechtotextwhisper
        ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    LIBRARY
        NAMELINK_SKIP
)

###
add_library(speechtotext_whisper MODULE)

ecm_qt_declare_logging_category(speechtotext_whisper
    HEADER speechtotext_whisper_debug.h
    IDENTIFIER SPEECHTOTEXT_WHISPER_LOG
    CATEGORY_NAME org.kde.kf.speechtotext.whisper
    DESCRIPTION "whisper speechtotext"
    EXPORT KTEXTADDONS
)
target_sources(
    speechtotext_whisper
    PRIVATE
        whisperspeechtotextclient.h
        whisperspeechtotextclient.cpp
        whisperspeechtotextplugin.h
        whisperspeechtotextplugin.cpp
)

target_link_libraries(
    speechtotext_whisper
    PRIVATE
        KF6::TextSpeechToText
        KF6::I18n
        speechtotextwhisper
)

install(TARGETS speechtotext_whisper DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/speechtotext/)

install(PROGRAMS scripts/whisper_helper.py DESTINATION ${KDE_INSTALL_BINDIR})

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
