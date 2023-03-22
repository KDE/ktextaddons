# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none
add_definitions(-DTRANSLATION_DOMAIN=\"libtexttranslator\")
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF${KF_MAJOR_VERSION}TextTranslator")




ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTTRANSLATE
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/texttranslator_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextTranslatorConfigVersion.cmake"
    SOVERSION 1
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextTranslatorConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextTranslatorConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KF${KF_MAJOR_VERSION}TextTranslatorTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF${KF_MAJOR_VERSION}TextTranslatorTargets.cmake NAMESPACE KF${KF_MAJOR_VERSION}::)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/texttranslator_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextTranslator/ COMPONENT Devel
    )

if(BUILD_DESIGNERPLUGIN)
    add_subdirectory(designer)
endif()

add_library(KF${KF_MAJOR_VERSION}TextTranslator )
add_library(KF${KF_MAJOR_VERSION}::TextTranslator ALIAS KF${KF_MAJOR_VERSION}TextTranslator)
ecm_qt_declare_logging_category(KF${KF_MAJOR_VERSION}TextTranslator HEADER texttranslator_debug.h
    IDENTIFIER TEXTTRANSLATOR_LOG CATEGORY_NAME org.kde.kf${KF_MAJOR_VERSION}.texttranslator
        DESCRIPTION "KF${KF_MAJOR_VERSION} (TextTranslator)"
        EXPORT KTEXTADDONS
    )

target_sources(KF${KF_MAJOR_VERSION}TextTranslator PRIVATE
    translator/misc/translatorutil.cpp
    translator/misc/translatorutil.h
    translator/misc/lineeditcatchreturnkey.cpp
    translator/misc/lineeditcatchreturnkey.h

    translator/widgets/translatorwidget.cpp
    translator/widgets/translatorwidget.h
    translator/widgets/translatordebugdialog.cpp
    translator/widgets/translatordebugdialog.h
    translator/widgets/translatorconfigurewidget.cpp
    translator/widgets/translatorconfigurewidget.h
    translator/widgets/translatorconfiguredialog.h
    translator/widgets/translatorconfiguredialog.cpp

    translator/widgets/translatorconfigurelistswidget.cpp
    translator/widgets/translatorconfigurelistswidget.h
    translator/widgets/translatorconfigurelanguagelistwidget.cpp
    translator/widgets/translatorconfigurelanguagelistwidget.h
    translator/widgets/translatorconfigurecombowidget.h
    translator/widgets/translatorconfigurecombowidget.cpp

    translator/widgets/translatormenu.cpp
    translator/widgets/translatormenu.h


    translator/networkmanager.cpp
    translator/networkmanager.h
    translator/translatorengineaccessmanager.h
    translator/translatorengineaccessmanager.cpp

    translator/translatorengineplugin.cpp
    translator/translatorengineplugin.h

    translator/translatorengineclient.h
    translator/translatorengineclient.cpp

    translator/translatorengineloader.cpp
    translator/translatorengineloader.h
    )
if (BUILD_TESTING)
    add_subdirectory(translator/autotests)
    add_subdirectory(translator/tests)
    add_subdirectory(translator/widgets/autotests)
endif()
add_subdirectory(translator/plugins)


if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF${KF_MAJOR_VERSION}TextTranslator PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KF${KF_MAJOR_VERSION}TextTranslator BASE_NAME texttranslator)


target_link_libraries(KF${KF_MAJOR_VERSION}TextTranslator
    PUBLIC
    Qt::Gui
    Qt::Widgets
    Qt::Network
    PRIVATE
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::WidgetsAddons
    KF${KF_MAJOR_VERSION}::ConfigGui
    )

target_include_directories(KF${KF_MAJOR_VERSION}TextTranslator INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextTranslator/>")

set_target_properties(KF${KF_MAJOR_VERSION}TextTranslator PROPERTIES
    VERSION ${TEXTTRANSLATE_VERSION}
    SOVERSION ${TEXTTRANSLATE_SOVERSION}
    EXPORT_NAME TextTranslator
    )

install(TARGETS
    KF${KF_MAJOR_VERSION}TextTranslator
    EXPORT KF${KF_MAJOR_VERSION}TextTranslatorTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS}
    )

ecm_generate_headers(TextTranslator_Camelcasetranslatorwidgets_HEADERS
    HEADER_NAMES
    TranslatorWidget
    TranslatorConfigureDialog
    TranslatorConfigureLanguageListWidget
    TranslatorConfigureListsWidget
    TranslatorMenu
    REQUIRED_HEADERS TextTranslator_translatorwidgets_HEADERS
    PREFIX TextTranslator
    RELATIVE translator/widgets/
    )

ecm_generate_headers(TextTranslator_Camelcasetranslator_HEADERS
    HEADER_NAMES
    TranslatorEnginePlugin
    TranslatorEngineClient
    TranslatorEngineAccessManager
    TranslatorEngineLoader
    REQUIRED_HEADERS TextTranslator_translator_HEADERS
    PREFIX TextTranslator
    RELATIVE translator
    )

ecm_generate_headers(TextTranslator_Camelcasetranslatormisc_HEADERS
    HEADER_NAMES
    TranslatorUtil
    REQUIRED_HEADERS TextTranslator_translatormisc_HEADERS
    PREFIX TextTranslator
    RELATIVE translator/misc/
    )

ecm_generate_pri_file(BASE_NAME TextTranslator
    LIB_NAME KF${KF_MAJOR_VERSION}TextTranslator
    DEPS "network" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF}/TextTranslator
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/texttranslator_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextTranslator/ COMPONENT Devel
    )

install(FILES
    ${TextTranslator_Camelcasetranslatorwidgets_HEADERS}
    ${TextTranslator_translatorwidgets_HEADERS}

    ${TextTranslator_Camelcasetranslatormisc_HEADERS}
    ${TextTranslator_translatormisc_HEADERS}

    ${TextTranslator_translator_HEADERS}
    ${TextTranslator_Camelcasetranslator_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextTranslator/TextTranslator
    COMPONENT Devel
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/texttranslator_export.h
    ${TextTranslator_translator_HEADERS}
    ${TextTranslator_translatorwidgets_HEADERS}
    ${TextTranslator_translatormisc_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextTranslator/texttranslator
    COMPONENT Devel
    )

install(FILES
    ${PRI_FILENAME}
    DESTINATION ${ECM_MKSPECS_INSTALL_DIR})


if (BUILD_QCH)
    ecm_add_qch(
        KF${KF_MAJOR_VERSION}TextTranslator_QCH
        NAME KF${KF_MAJOR_VERSION}TextTranslator
        BASE_NAME KF${KF_MAJOR_VERSION}TextTranslator
        VERSION ${TEXTTRANSLATE_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${TextTranslator_translator_HEADERS}
        ${TextTranslator_translatorwidgets_HEADERS}
        ${TextTranslator_translatormisc_HEADERS}
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
        TARGETS KF${KF_MAJOR_VERSION}TextTranslator_QCH
        FILE KF${KF_MAJOR_VERSION}TextTranslatorQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF${KF_MAJOR_VERSION}TextTranslatorQchTargets.cmake\")")
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextTranslatorConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextTranslatorConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )
