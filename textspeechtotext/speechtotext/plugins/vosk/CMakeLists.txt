# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

find_package(vosk)

configure_file(config-vosk-plugin.h.in ${CMAKE_CURRENT_BINARY_DIR}/config-vosk-plugin.h)

add_library(voskspeechtotext)

target_sources(voskspeechtotext PRIVATE
    voskspeechtotextmodel.h
    voskspeechtotextmodel.cpp
    voskspeechtotextproxymodel.cpp
    voskspeechtotextproxymodel.h

    managermodelvoskspeechtotext.h
    managermodelvoskspeechtotext.cpp

    voskspeechtotextinfo.h
    voskspeechtotextinfo.cpp

    voskdownloadlanguagejob.cpp
    voskdownloadlanguagejob.h

    generateinstalledlanguageinfojob.h
    generateinstalledlanguageinfojob.cpp

    voskextractlanguagejob.h
    voskextractlanguagejob.cpp

    voskengineutils.cpp
    voskengineutils.h

    voskenginelanguagewidget.h
    voskenginelanguagewidget.cpp

    voskengineutils.h
    voskengineutils.cpp

    voskenginedialog.h
    voskenginedialog.cpp


    voskspeechtotextdevice.h
    voskspeechtotextdevice.cpp

)

generate_export_header(voskspeechtotext BASE_NAME libvoskspeechtotext)

ecm_qt_declare_logging_category(voskspeechtotext HEADER libvoskspeechtotext_debug.h IDENTIFIER  LIBVOSKSPEECHTOTEXT_LOG
    CATEGORY_NAME org.kde.voskspeechtotext DESCRIPTION "lib vosk speech to text" EXPORT KTEXTADDONS)

target_link_libraries(voskspeechtotext
    Qt::Widgets
    KF${KF_MAJOR_VERSION}::Archive
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::TextSpeechToText
    KF${KF_MAJOR_VERSION}::WidgetsAddons
    KF${KF_MAJOR_VERSION}::ConfigWidgets
    KF${KF_MAJOR_VERSION}::KIOCore
)

set_target_properties(voskspeechtotext
    PROPERTIES OUTPUT_NAME voskspeechtotext VERSION ${TEXTSPEECHTOTEXT_VERSION} SOVERSION ${TEXTSPEECHTOTEXT_SOVERSION}
)

install(TARGETS voskspeechtotext ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)


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

)

target_link_libraries(speechtotext_vosk PRIVATE KF${KF_MAJOR_VERSION}::TextSpeechToText KF${KF_MAJOR_VERSION}::I18n voskspeechtotext)

install(TARGETS speechtotext_vosk  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf${QT_MAJOR_VERSION}/speechtotext/)

if (BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()
