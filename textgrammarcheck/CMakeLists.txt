# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

add_definitions(-DTRANSLATION_DOMAIN=\"libtextgrammarcheck\")

set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF6TextGrammarCheck")
if(BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF6TextGrammarCheck_QCH
        FILE KF6TextGrammarCheckQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
)
set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF6TextGrammarCheckQchTargets.cmake\")")
endif()
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextGrammarCheckConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextGrammarCheckConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
)


ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTGRAMMARCHECK
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textgrammarcheck_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF6TextGrammarCheckConfigVersion.cmake"
    SOVERSION 1
)

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextGrammarCheckConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextGrammarCheckConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(EXPORT KF6TextGrammarCheckTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF6TextGrammarCheckTargets.cmake NAMESPACE KF6::)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textgrammarcheck_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextGrammarCheck/ COMPONENT Devel
)

add_library(KF6TextGrammarCheck)
add_library(KF6::TextGrammarCheck ALIAS KF6TextGrammarCheck)
ecm_qt_declare_logging_category(KF6TextGrammarCheck HEADER textgrammarcheck_debug.h
    IDENTIFIER TEXTGRAMMARCHECK_LOG
    CATEGORY_NAME org.kde.kf.textgrammarcheck
    OLD_CATEGORY_NAMES org.kde.kf6.textgrammarcheck
        DESCRIPTION "KF6 (Text Grammar Check)"
        EXPORT KTEXTADDONS
)

target_sources(KF6TextGrammarCheck PRIVATE
    common/grammarerror.cpp
    common/grammarerror.h
    common/grammaraction.h
    common/grammaraction.cpp
    common/grammarresultwidget.cpp
    common/grammarresultwidget.h
    common/grammarresulttextedit.cpp
    common/grammarresulttextedit.h
    common/grammarresultutil.h
    common/grammarresultutil.cpp

    languagetool/languageinfo.cpp
    languagetool/languageinfo.h
    languagetool/languagetoolcombobox.cpp
    languagetool/languagetoolcombobox.h
    languagetool/languagetoolconfigdialog.cpp
    languagetool/languagetoolconfigdialog.h
    languagetool/languagetoolconfigwidget.cpp
    languagetool/languagetoolconfigwidget.h
    languagetool/languagetoolgetlistoflanguagejob.cpp
    languagetool/languagetoolgetlistoflanguagejob.h
    languagetool/languagetoolgrammarerror.cpp
    languagetool/languagetoolgrammarerror.h
    languagetool/languagetoollistoflanguagesparser.cpp
    languagetool/languagetoollistoflanguagesparser.h
    languagetool/languagetoolmanager.cpp
    languagetool/languagetoolmanager.h
    languagetool/languagetoolparser.cpp
    languagetool/languagetoolparser.h
    languagetool/languagetoolresultjob.cpp
    languagetool/languagetoolresultjob.h
    languagetool/languagetoolresultwidget.cpp
    languagetool/languagetoolresultwidget.h
    languagetool/languagetoolupdatecombobox.cpp
    languagetool/languagetoolupdatecombobox.h

    grammalecte/grammalecteconfigdialog.cpp
    grammalecte/grammalecteconfigdialog.h
    grammalecte/grammalecteconfigwidget.cpp
    grammalecte/grammalecteconfigwidget.h
    grammalecte/grammalectegenerateconfigoptionjob.cpp
    grammalecte/grammalectegenerateconfigoptionjob.h
    grammalecte/grammalectegrammarerror.cpp
    grammalecte/grammalectegrammarerror.h
    grammalecte/grammalectemanager.cpp
    grammalecte/grammalectemanager.h
    grammalecte/grammalecteparser.cpp
    grammalecte/grammalecteparser.h
    grammalecte/grammalecteresultjob.cpp
    grammalecte/grammalecteresultjob.h
    grammalecte/grammalecteresultwidget.cpp
    grammalecte/grammalecteresultwidget.h
    grammalecte/grammalecteurlrequesterwidget.h
    grammalecte/grammalecteurlrequesterwidget.cpp
)
if(BUILD_TESTING)
    add_subdirectory(grammalecte/autotests)
    add_subdirectory(grammalecte/tests)
    add_subdirectory(languagetool/autotests)
    add_subdirectory(languagetool/tests)
    add_subdirectory(common/autotests/)
endif()

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF6TextGrammarCheck PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KF6TextGrammarCheck BASE_NAME textgrammarcheck)


target_link_libraries(KF6TextGrammarCheck
    PUBLIC
    Qt::Gui
    Qt::Widgets
    PRIVATE
    Qt::Network
    KF6::I18n
    KF6::WidgetsAddons
    KF6::ConfigCore
    KF6::ConfigGui
    KF6::ColorScheme
)

target_include_directories(KF6TextGrammarCheck INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextGrammarCheck/>")

set_target_properties(KF6TextGrammarCheck PROPERTIES
    VERSION ${TEXTGRAMMARCHECK_VERSION}
    SOVERSION ${TEXTGRAMMARCHECK_SOVERSION}
    EXPORT_NAME TextGrammarCheck
)

install(TARGETS
    KF6TextGrammarCheck
    EXPORT KF6TextGrammarCheckTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
)

ecm_generate_headers(TextGrammarCheck_Camelcasecommon_HEADERS
    HEADER_NAMES
    GrammarAction
    GrammarError
    GrammarResultTextEdit
    GrammarResultWidget
    REQUIRED_HEADERS TextGrammarCheck_common_HEADERS
    PREFIX TextGrammarCheck
    RELATIVE common/
)

ecm_generate_headers(TextGrammarCheck_Camelcasegrammalecte_HEADERS
    HEADER_NAMES
    GrammalecteConfigDialog
    GrammalecteConfigWidget
    GrammalecteManager
    GrammalecteResultWidget
    GrammalecteGenerateConfigOptionJob
    GrammalecteResultJob
    REQUIRED_HEADERS TextGrammarCheck_grammalecte_HEADERS
    PREFIX TextGrammarCheck
    RELATIVE grammalecte/
)

ecm_generate_headers(TextGrammarCheck_Camelcaselanguagetool_HEADERS
    HEADER_NAMES
    LanguageToolComboBox
    LanguageToolConfigDialog
    LanguageToolConfigWidget
    LanguageToolGetListOfLanguageJob
    LanguageToolManager
    LanguageToolResultWidget
    REQUIRED_HEADERS TextGrammarCheck_languagetool_HEADERS
    PREFIX TextGrammarCheck
    RELATIVE languagetool/
)


install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textgrammarcheck_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextGrammarCheck/ COMPONENT Devel
)

install(FILES
    ${TextGrammarCheck_common_HEADERS}
    ${TextGrammarCheck_Camelcasecommon_HEADERS}

    ${TextGrammarCheck_grammalecte_HEADERS}
    ${TextGrammarCheck_Camelcasegrammalecte_HEADERS}

    ${TextGrammarCheck_languagetool_HEADERS}
    ${TextGrammarCheck_Camelcaselanguagetool_HEADERS}

    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextGrammarCheck/TextGrammarCheck
    COMPONENT Devel
)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textgrammarcheck_export.h
    ${TextGrammarCheck_common_HEADERS}
    ${TextGrammarCheck_grammalecte_HEADERS}
    ${TextGrammarCheck_languagetool_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextGrammarCheck/textgrammarcheck
    COMPONENT Devel
)


if(BUILD_QCH)
    ecm_add_qch(
        KF6TextGrammarCheck_QCH
        NAME KF6TextGrammarCheck
        BASE_NAME KF6TextGrammarCheck
        VERSION ${TEXTGRAMMARCHECK_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${TextGrammarCheck_common_HEADERS}
        ${TextGrammarCheck_grammalecte_HEADERS}
        ${TextGrammarCheck_languagetool_HEADERS}
        LINK_QCHS
            Qt6Core_QCH
            Qt6Gui_QCH
            Qt6Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            TEXTGRAMMARCHECK_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
)
endif()
