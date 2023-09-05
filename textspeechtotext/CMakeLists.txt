# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: none
add_definitions(-DTRANSLATION_DOMAIN=\"libtextspeechtotext\")
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF${KF_MAJOR_VERSION}TextSpeechToText")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTTRANSLATE
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textspeechtotext_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextSpeechToTextConfigVersion.cmake"
    SOVERSION 1
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextSpeechToTextConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextSpeechToTextConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KF${KF_MAJOR_VERSION}TextSpeechToTextTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KF${KF_MAJOR_VERSION}TextSpeechToTextTargets.cmake NAMESPACE KF${KF_MAJOR_VERSION}::)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textspeechtotext_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextSpeechToText/ COMPONENT Devel
    )

add_library(KF${KF_MAJOR_VERSION}TextSpeechToText)
add_library(KF${KF_MAJOR_VERSION}::TextSpeechToText ALIAS KF${KF_MAJOR_VERSION}TextSpeechToText)
ecm_qt_declare_logging_category(KF${KF_MAJOR_VERSION}TextSpeechToText HEADER textspeechtotext_debug.h
    IDENTIFIER TEXTSPEECHTOTEXT_LOG
    CATEGORY_NAME org.kde.kf.textspeechtotext
    DESCRIPTION "KF${KF_MAJOR_VERSION} (TextSpeechToText)"
    EXPORT KTEXTADDONS
)

target_sources(KF${KF_MAJOR_VERSION}TextSpeechToText PRIVATE
    speechtotextclient.h
    speechtotextclient.cpp
    )
#if (BUILD_TESTING)
#    add_subdirectory(translator/autotests)
#    add_subdirectory(translator/tests)
#    add_subdirectory(translator/widgets/autotests)
#endif()
#add_subdirectory(translator/plugins)


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF${KF_MAJOR_VERSION}TextSpeechToText PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KF${KF_MAJOR_VERSION}TextSpeechToText BASE_NAME textspeechtotext)


target_link_libraries(KF${KF_MAJOR_VERSION}TextSpeechToText
    PUBLIC
    Qt::Gui
    Qt::Widgets
    Qt::Network
    PRIVATE
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::WidgetsAddons
    KF${KF_MAJOR_VERSION}::ConfigGui
    KF${KF_MAJOR_VERSION}::TextAddonsWidgets
    )

target_include_directories(KF${KF_MAJOR_VERSION}TextSpeechToText INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextSpeechToText/>")

set_target_properties(KF${KF_MAJOR_VERSION}TextSpeechToText PROPERTIES
    VERSION ${TEXTTRANSLATE_VERSION}
    SOVERSION ${TEXTTRANSLATE_SOVERSION}
    EXPORT_NAME TextSpeechToText
    )

install(TARGETS
    KF${KF_MAJOR_VERSION}TextSpeechToText
    EXPORT KF${KF_MAJOR_VERSION}TextSpeechToTextTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    )

#ecm_generate_headers(TextSpeechToText_Camelcasetranslatorwidgets_HEADERS
#    HEADER_NAMES
#    TranslatorWidget
#    TranslatorConfigureDialog
#    TranslatorConfigureLanguageListWidget
#    TranslatorConfigureListsWidget
#    TranslatorMenu
#    REQUIRED_HEADERS TextSpeechToText_translatorwidgets_HEADERS
#    PREFIX TextSpeechToText
#    RELATIVE translator/widgets/
#    )

#ecm_generate_headers(TextSpeechToText_Camelcasetranslator_HEADERS
#    HEADER_NAMES
#    TranslatorEnginePlugin
#    TranslatorEngineClient
#    TranslatorEngineAccessManager
#    TranslatorEngineLoader
#    REQUIRED_HEADERS TextSpeechToText_translator_HEADERS
#    PREFIX TextSpeechToText
#    RELATIVE translator
#    )

#ecm_generate_headers(TextSpeechToText_Camelcasetranslatormisc_HEADERS
#    HEADER_NAMES
#    TranslatorUtil
#    REQUIRED_HEADERS TextSpeechToText_translatormisc_HEADERS
#    PREFIX TextSpeechToText
#    RELATIVE translator/misc/
#    )

ecm_generate_pri_file(BASE_NAME TextSpeechToText
    LIB_NAME KF${KF_MAJOR_VERSION}TextSpeechToText
    DEPS "network" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF}/TextSpeechToText
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textspeechtotext_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextSpeechToText/ COMPONENT Devel
    )

install(FILES
#    ${TextSpeechToText_Camelcasetranslatorwidgets_HEADERS}
#    ${TextSpeechToText_translatorwidgets_HEADERS}

#    ${TextSpeechToText_Camelcasetranslatormisc_HEADERS}
#    ${TextSpeechToText_translatormisc_HEADERS}

#    ${TextSpeechToText_translator_HEADERS}
#    ${TextSpeechToText_Camelcasetranslator_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextSpeechToText/TextSpeechToText
    COMPONENT Devel
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textspeechtotext_export.h
#    ${TextSpeechToText_translator_HEADERS}
#    ${TextSpeechToText_translatorwidgets_HEADERS}
#    ${TextSpeechToText_translatormisc_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextSpeechToText/textspeechtotext
    COMPONENT Devel
    )

install(FILES
    ${PRI_FILENAME}
    DESTINATION ${ECM_MKSPECS_INSTALL_DIR})


if (BUILD_QCH)
    ecm_add_qch(
        KF${KF_MAJOR_VERSION}TextSpeechToText_QCH
        NAME KF${KF_MAJOR_VERSION}TextSpeechToText
        BASE_NAME KF${KF_MAJOR_VERSION}TextSpeechToText
        VERSION ${TEXTTRANSLATE_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${TextSpeechToText_translator_HEADERS}
        ${TextSpeechToText_translatorwidgets_HEADERS}
        ${TextSpeechToText_translatormisc_HEADERS}
        LINK_QCHS
            Qt${QT_MAJOR_VERSION}Core_QCH
            Qt${QT_MAJOR_VERSION}Gui_QCH
            Qt${QT_MAJOR_VERSION}Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            TEXTTRANSLATE_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()
if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF${KF_MAJOR_VERSION}TextSpeechToText_QCH
        FILE KF${KF_MAJOR_VERSION}TextSpeechToTextQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF${KF_MAJOR_VERSION}TextSpeechToTextQchTargets.cmake\")")
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextSpeechToTextConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextSpeechToTextConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )
