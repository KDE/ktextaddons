# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>
add_library(speechtotext_whisper MODULE)

ecm_qt_declare_logging_category(speechtotext_debug_whisper_SRCS
    HEADER speechtotext_whisper_debug.h
    IDENTIFIER SPEECHTOTEXT_WHISPER_LOG
    CATEGORY_NAME org.kde.kf.speechtotext.whisper
    DESCRIPTION "whisper speechtotext"
    EXPORT KTEXTADDONS
)
target_sources(speechtotext_whisper PRIVATE
    ${speechtotext_debug_whisper_SRCS}
    whisperspeechtotextclient.h
    whisperspeechtotextclient.cpp

    whisperspeechtotextplugin.h
    whisperspeechtotextplugin.cpp
)

target_link_libraries(speechtotext_whisper PRIVATE KF${KF_MAJOR_VERSION}::TextSpeechToText KF${KF_MAJOR_VERSION}::I18n)

install(TARGETS speechtotext_whisper  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf${QT_MAJOR_VERSION}/speechtotext/)
