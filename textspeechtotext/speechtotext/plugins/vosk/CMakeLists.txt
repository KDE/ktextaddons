# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

add_library(libvoskspeechtotext)

target_sources(libvoskspeechtotext PRIVATE
    voskspeechtotextmodel.h
    voskspeechtotextmodel.cpp
    voskspeechtotextproxymodel.cpp
    voskspeechtotextproxymodel.h

    managermodelvoskspeechtotext.h
    managermodelvoskspeechtotext.cpp

    voskspeechtotextinfo.h
    voskspeechtotextinfo.cpp

    downloadlanguagejob.cpp
    downloadlanguagejob.h

    generateinstalledlanguageinfojob.h
    generateinstalledlanguageinfojob.cpp

    extractlanguagejob.h
    extractlanguagejob.cpp

    voskengineutils.cpp
    voskengineutils.h

    voskenginelanguagewidget.h
    voskenginelanguagewidget.cpp

    voskengineutils.h
    voskengineutils.cpp

    voskenginedialog.h
    voskenginedialog.cpp
)

generate_export_header(libvoskspeechtotext BASE_NAME libvoskspeechtotext)

ecm_qt_declare_logging_category(libvoskspeechtotext HEADER libvoskspeechtotext_debug.h IDENTIFIER  LIBVOSKSPEECHTOTEXT_LOG
    CATEGORY_NAME org.kde.libvoskspeechtotext DESCRIPTION "lib speech to text" EXPORT KTEXTADDONS)

target_link_libraries(libvoskspeechtotext
    Qt::Widgets
    KF${KF_MAJOR_VERSION}::Archive
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::TextSpeechToText
    KF${KF_MAJOR_VERSION}::WidgetsAddons
    KF${KF_MAJOR_VERSION}::ConfigWidgets
)

set_target_properties(libvoskspeechtotext
    PROPERTIES OUTPUT_NAME libvoskspeechtotext VERSION ${TEXTSPEECHTOTEXT_VERSION} SOVERSION ${TEXTSPEECHTOTEXT_SOVERSION}
)

install(TARGETS libvoskspeechtotext ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)


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
)

target_link_libraries(speechtotext_vosk PRIVATE KF${KF_MAJOR_VERSION}::TextSpeechToText KF${KF_MAJOR_VERSION}::I18n libvoskspeechtotext)

install(TARGETS speechtotext_vosk  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf${QT_MAJOR_VERSION}/speechtotext/)

if (BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()
