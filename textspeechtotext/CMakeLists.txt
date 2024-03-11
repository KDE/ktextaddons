# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
add_definitions(-DTRANSLATION_DOMAIN=\"libtextspeechtotext\")
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF6TextSpeechToText")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTSPEECHTOTEXT
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textspeechtotext_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF6TextSpeechToTextConfigVersion.cmake"
    SOVERSION 1
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextSpeechToTextConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextSpeechToTextConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KF6TextSpeechToTextTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KF6TextSpeechToTextTargets.cmake NAMESPACE KF6::)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textspeechtotext_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextSpeechToText/ COMPONENT Devel
    )

add_library(KF6TextSpeechToText)
add_library(KF6::TextSpeechToText ALIAS KF6TextSpeechToText)
ecm_qt_declare_logging_category(KF6TextSpeechToText HEADER textspeechtotext_debug.h
    IDENTIFIER TEXTSPEECHTOTEXT_LOG
    CATEGORY_NAME org.kde.kf.textspeechtotext
    DESCRIPTION "KF6 (TextSpeechToText)"
    EXPORT KTEXTADDONS
)

target_sources(KF6TextSpeechToText PRIVATE
    speechtotext/speechtotextclient.h
    speechtotext/speechtotextclient.cpp

    speechtotext/speechtotextplugin.h
    speechtotext/speechtotextplugin.cpp

    speechtotext/speechtotextengineloader.cpp
    speechtotext/speechtotextengineloader.h

    speechtotext/speechtotextmanager.h
    speechtotext/speechtotextmanager.cpp    

    speechtotext/speechtotextengineaccessmanager.cpp
    speechtotext/speechtotextengineaccessmanager.h

    speechtotext/widgets/speechtotextconfigurewidget.h
    speechtotext/widgets/speechtotextconfigurewidget.cpp

    speechtotext/widgets/speechtotextconfiguredialog.h
    speechtotext/widgets/speechtotextconfiguredialog.cpp

    speechtotext/widgets/speechtotextcomboboxwidget.h
    speechtotext/widgets/speechtotextcomboboxwidget.cpp

    speechtotext/widgets/speechtotextselectdevicewidget.h
    speechtotext/widgets/speechtotextselectdevicewidget.cpp

    speechtotext/widgets/speechtotexttoolbuttonwidget.h
    speechtotext/widgets/speechtotexttoolbuttonwidget.cpp

    speechtotext/widgets/speechtotextaction.h
    speechtotext/widgets/speechtotextaction.cpp

    speechtotext/widgets/speechtotextmenu.h
    speechtotext/widgets/speechtotextmenu.cpp

    speechtotext/textspeechtotextutil.h
    speechtotext/textspeechtotextutil.cpp
    )

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF6TextSpeechToText PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KF6TextSpeechToText BASE_NAME textspeechtotext)


target_link_libraries(KF6TextSpeechToText
    PUBLIC
    Qt::Gui
    Qt::Widgets
    Qt::Network
    PRIVATE
    Qt::MultimediaWidgets
    KF6::I18n
    KF6::WidgetsAddons
    KF6::ConfigGui
    KF6::TextAddonsWidgets
    )

target_include_directories(KF6TextSpeechToText INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextSpeechToText/>")

set_target_properties(KF6TextSpeechToText PROPERTIES
    VERSION ${TEXTSPEECHTOTEXT_VERSION}
    SOVERSION ${TEXTSPEECHTOTEXT_SOVERSION}
    EXPORT_NAME TextSpeechToText
    )

install(TARGETS
    KF6TextSpeechToText
    EXPORT KF6TextSpeechToTextTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    )

ecm_generate_headers(TextSpeechToText_Camelcasespeechtotext_HEADERS
    HEADER_NAMES
    SpeechToTextClient
    SpeechToTextPlugin
    SpeechToTextEngineLoader
    SpeechToTextManager
    REQUIRED_HEADERS TextSpeechToText_speechtotext_HEADERS
    PREFIX TextSpeechToText
    RELATIVE speechtotext
)

ecm_generate_headers(TextSpeechToTextWidget_Camelcasespeechtotext_HEADERS
    HEADER_NAMES
    SpeechToTextAction
    SpeechToTextToolButtonWidget
    SpeechToTextMenu
    REQUIRED_HEADERS TextSpeechToTextWidget_speechtotext_HEADERS
    PREFIX TextSpeechToText
    RELATIVE speechtotext/widgets
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textspeechtotext_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextSpeechToText/ COMPONENT Devel
    )

install(FILES
    ${TextSpeechToText_Camelcasespeechtotext_HEADERS}
    ${TextSpeechToTextWidget_Camelcasespeechtotext_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextSpeechToText/TextSpeechToText
    COMPONENT Devel
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textspeechtotext_export.h
    ${TextSpeechToText_speechtotext_HEADERS}
    ${TextSpeechToTextWidget_speechtotext_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextSpeechToText/textspeechtotext
    COMPONENT Devel
    )


if (BUILD_QCH)
    ecm_add_qch(
        KF6TextSpeechToText_QCH
        NAME KF6TextSpeechToText
        BASE_NAME KF6TextSpeechToText
        VERSION ${TEXTSPEECHTOTEXT_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${TextSpeechToText_speechtotext_HEADERS}
        ${TextSpeechToTextWidget_speechtotext_HEADERS}
        LINK_QCHS
            Qt6Core_QCH
            Qt6Gui_QCH
            Qt6Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            TEXTSPEECHTOTEXT_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()
if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF6TextSpeechToText_QCH
        FILE KF6TextSpeechToTextQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF6TextSpeechToTextQchTargets.cmake\")")
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextSpeechToTextConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextSpeechToTextConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )

add_subdirectory(speechtotext/plugins)
if(BUILD_TESTING)
    add_subdirectory(speechtotext/widgets/autotests)
    add_subdirectory(speechtotext/widgets/tests)
    add_subdirectory(tests)
endif()
