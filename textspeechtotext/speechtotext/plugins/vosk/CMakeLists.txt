# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

# TODO reenable it
set(HAVE_VOSK_API_SUPPORT TRUE)
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
    KF6::Archive
    KF6::I18n
    KF6::TextSpeechToText
    KF6::WidgetsAddons
    KF6::ConfigWidgets
    Vosk
)

set_target_properties(voskspeechtotext
    PROPERTIES OUTPUT_NAME voskspeechtotext VERSION ${TEXTSPEECHTOTEXT_VERSION} SOVERSION ${TEXTSPEECHTOTEXT_SOVERSION}
)

install(TARGETS voskspeechtotext ${KDE_INSTALL_TARGETS_DEFAULT_ARGS} LIBRARY NAMELINK_SKIP)

# Improve it. We need to fix on windows too.
install(FILES "${CMAKE_BINARY_DIR}/vosk/libvosk.so" DESTINATION ${KDE_INSTALL_LIBDIR})


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

target_link_libraries(speechtotext_vosk PRIVATE KF6::TextSpeechToText KF6::I18n voskspeechtotext)

install(TARGETS speechtotext_vosk  DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/speechtotext/)

if (BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()
