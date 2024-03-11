# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
add_library(speechtotext_google MODULE)

ecm_qt_declare_logging_category(speechtotext_google
    HEADER speechtotext_google_debug.h
    IDENTIFIER SPEECHTOTEXT_GOOGLE_LOG
    CATEGORY_NAME org.kde.kf.speechtotext.google
    DESCRIPTION "google speechtotext"
    EXPORT KTEXTADDONS
)
target_sources(speechtotext_google PRIVATE
    googlespeechtotextclient.h
    googlespeechtotextclient.cpp

    googlespeechtotextplugin.h
    googlespeechtotextplugin.cpp

    googlespeechtotextpluginjob.h
    googlespeechtotextpluginjob.cpp
)

target_link_libraries(speechtotext_google PRIVATE KF6::TextSpeechToText KF6::I18n)

install(TARGETS speechtotext_google  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/speechtotext/)
