# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: none
add_library(speechtotext_google MODULE)

ecm_qt_declare_logging_category(speechtotext_debug_google_SRCS
    HEADER speechtotext_debug.h
    IDENTIFIER SPEECHTOTEXT_GOOGLE_LOG
    CATEGORY_NAME org.kde.kf.speechtotext.google
    DESCRIPTION "google speechtotext"
    EXPORT KTEXTADDONS
)
target_sources(speechtotext_google PRIVATE
    ${speechtotext_debug_google_SRCS}
    googlespeechtotextclient.h
    googlespeechtotextclient.cpp

    googlespeechtotextplugin.h
    googlespeechtotextplugin.cpp
)

target_link_libraries(speechtotext_google PRIVATE KF${KF_MAJOR_VERSION}::TextSpeechToText KF${KF_MAJOR_VERSION}::I18n)

install(TARGETS speechtotext_google  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf${QT_MAJOR_VERSION}/speechtotext/)
