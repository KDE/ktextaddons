# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>
add_definitions(-DTRANSLATION_DOMAIN=\"libtexttranslator\")
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF6TextTranslator")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTTRANSLATE
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/texttranslator_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF6TextTranslatorConfigVersion.cmake"
    SOVERSION 1
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextTranslatorConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextTranslatorConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(EXPORT KF6TextTranslatorTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF6TextTranslatorTargets.cmake NAMESPACE KF6::)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/texttranslator_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextTranslator/ COMPONENT Devel
)

if(BUILD_DESIGNERPLUGIN)
    add_subdirectory(designer)
endif()

add_library(KF6TextTranslator)
add_library(KF6::TextTranslator ALIAS KF6TextTranslator)
ecm_qt_declare_logging_category(KF6TextTranslator HEADER texttranslator_debug.h
    IDENTIFIER TEXTTRANSLATOR_LOG
    CATEGORY_NAME org.kde.kf.texttranslator
    OLD_CATEGORY_NAMES org.kde.kf6.texttranslator
    DESCRIPTION "KF6 (TextTranslator)"
    EXPORT KTEXTADDONS
)

target_sources(KF6TextTranslator PRIVATE
    translator/misc/translatorutil.cpp
    translator/misc/translatorutil.h

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

    translator/widgets/translatorconfigurelanguagesortfilterproxymodel.h
    translator/widgets/translatorconfigurelanguagesortfilterproxymodel.cpp

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
if(BUILD_TESTING)
    add_subdirectory(translator/autotests)
    add_subdirectory(translator/tests)
    add_subdirectory(translator/widgets/autotests)
endif()
add_subdirectory(translator/plugins)


if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF6TextTranslator PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KF6TextTranslator BASE_NAME texttranslator)


target_link_libraries(KF6TextTranslator
    PUBLIC
    Qt::Gui
    Qt::Widgets
    Qt::Network
    PRIVATE
    KF6::I18n
    KF6::WidgetsAddons
    KF6::ConfigGui
    KF6::TextAddonsWidgets
)

target_include_directories(KF6TextTranslator INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextTranslator/>")

set_target_properties(KF6TextTranslator PROPERTIES
    VERSION ${TEXTTRANSLATE_VERSION}
    SOVERSION ${TEXTTRANSLATE_SOVERSION}
    EXPORT_NAME TextTranslator
)

install(TARGETS
    KF6TextTranslator
    EXPORT KF6TextTranslatorTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
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


if(BUILD_QCH)
    ecm_add_qch(
        KF6TextTranslator_QCH
        NAME KF6TextTranslator
        BASE_NAME KF6TextTranslator
        VERSION ${TEXTTRANSLATE_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${TextTranslator_translator_HEADERS}
        ${TextTranslator_translatorwidgets_HEADERS}
        ${TextTranslator_translatormisc_HEADERS}
        LINK_QCHS
            Qt6Core_QCH
            Qt6Gui_QCH
            Qt6Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            TEXTTRANSLATE_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
)
endif()
if(BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF6TextTranslator_QCH
        FILE KF6TextTranslatorQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
)
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF6TextTranslatorQchTargets.cmake\")")
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextTranslatorConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextTranslatorConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)
