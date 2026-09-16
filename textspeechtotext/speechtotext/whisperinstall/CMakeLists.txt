# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

# Everything needed to check and install the python side of whisper, without
# the client itself: an application can offer the installation without pulling
# the speech to text plugin.
add_library(speechtotextwhisperinstall)
ecm_qt_declare_logging_category(speechtotextwhisperinstall
    HEADER speechtotextwhisperinstall_lib_debug.h
    IDENTIFIER SPEECHTOTEXT_WHISPERINSTALL_LIB_LOG
    CATEGORY_NAME org.kde.kf.speechtotext_lib.whisperinstall
    DESCRIPTION "whisper install speech to text lib"
    EXPORT KTEXTADDONS
)

target_sources(
    speechtotextwhisperinstall
    PRIVATE
        whisperspeechtotextutils.h
        whisperspeechtotextutils.cpp
        whisperspeechtotextcheckjob.h
        whisperspeechtotextcheckjob.cpp
        whisperspeechtotextinstalljob.h
        whisperspeechtotextinstalljob.cpp
        whisperspeechtotextinstallpythonevenvjob.h
        whisperspeechtotextinstallpythonevenvjob.cpp
        whisperspeechtotextinstallpythonwidget.h
        whisperspeechtotextinstallpythonwidget.cpp
        whisperspeechtotextinstallpythondialog.h
        whisperspeechtotextinstallpythondialog.cpp
        whisperspeechtotextinstallmessagewidget.h
        whisperspeechtotextinstallmessagewidget.cpp
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        speechtotextwhisperinstall
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
generate_export_header(speechtotextwhisperinstall BASE_NAME speechtotextwhisperinstall)

# The headers are not installed: the sources of this repository which link
# against it include them from the build tree.
target_include_directories(
    speechtotextwhisperinstall
    PUBLIC
        $<BUILD_INTERFACE:${CMAKE_CURRENT_SOURCE_DIR}>
        $<BUILD_INTERFACE:${CMAKE_CURRENT_BINARY_DIR}>
)

target_link_libraries(
    speechtotextwhisperinstall
    PUBLIC
        Qt::Widgets
        KF6::WidgetsAddons
    PRIVATE
        KF6::I18n
        KF6::ConfigCore
        KF6::TextAddonsWidgets
)

set_target_properties(
    speechtotextwhisperinstall
    PROPERTIES
        VERSION
            ${TEXTSPEECHTOTEXT_VERSION}
        SOVERSION
            ${TEXTSPEECHTOTEXT_SOVERSION}
        EXPORT_NAME
            speechtotextwhisperinstall
)

install(
    TARGETS
        speechtotextwhisperinstall
    EXPORT KF6TextSpeechToTextTargets
    ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    LIBRARY
        NAMELINK_SKIP
)

# The backend script: the check and the install need it as much as the client does,
# and WhisperSpeechToTextUtils::pythonScriptPath() is the one which locates it.
install(PROGRAMS scripts/whisper_helper.py DESTINATION ${KDE_INSTALL_BINDIR})

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
