# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>
add_library(speechtotext_vosk MODULE)

ecm_qt_declare_logging_category(speechtotext_vosk
    HEADER speechtotext_vosk_debug.h
    IDENTIFIER SPEECHTOTEXT_VOSK_LOG
    CATEGORY_NAME org.kde.kf.speechtotext.vosk
    DESCRIPTION "vosk speechtotext"
    EXPORT KTEXTADDONS
)
target_sources(speechtotext_vosk PRIVATE
    voskspeechtotextclient.h
    voskspeechtotextclient.cpp

    voskspeechtotextplugin.h
    voskspeechtotextplugin.cpp

    voskspeechtotextpluginjob.h
    voskspeechtotextpluginjob.cpp

    voskspeechtotextmodel.h
    voskspeechtotextmodel.cpp

    voskspeechtotextinfo.h
    voskspeechtotextinfo.cpp
)

target_link_libraries(speechtotext_vosk PRIVATE KF${KF_MAJOR_VERSION}::TextSpeechToText KF${KF_MAJOR_VERSION}::I18n)

install(TARGETS speechtotext_vosk  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf${QT_MAJOR_VERSION}/speechtotext/)
