# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: none

add_definitions(-DTRANSLATION_DOMAIN=\"libtextgrammarcheck\")

set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF${KF_MAJOR_VERSION}TextGrammarCheck")
if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF${KF_MAJOR_VERSION}TextGrammarCheck_QCH
        FILE KF${KF_MAJOR_VERSION}TextGrammarCheckQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF${KF_MAJOR_VERSION}TextGrammarCheckQchTargets.cmake\")")
endif()
configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextGrammarCheckConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextGrammarCheckConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )


ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTGRAMMARCHECK
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textgrammarcheck_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextGrammarCheckConfigVersion.cmake"
    SOVERSION 1
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextGrammarCheckConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextGrammarCheckConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KF${KF_MAJOR_VERSION}TextGrammarCheckTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF${KF_MAJOR_VERSION}TextGrammarCheckTargets.cmake NAMESPACE KF${KF_MAJOR_VERSION}::)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textgrammarcheck_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextGrammarCheck/ COMPONENT Devel
    )

add_library(KF${KF_MAJOR_VERSION}TextGrammarCheck )
add_library(KF${KF_MAJOR_VERSION}::TextGrammarCheck ALIAS KF${KF_MAJOR_VERSION}TextGrammarCheck)
ecm_qt_declare_logging_category(KF${KF_MAJOR_VERSION}TextGrammarCheck HEADER textgrammarcheck_debug.h
    IDENTIFIER TEXTGRAMMARCHECK_LOG
    CATEGORY_NAME org.kde.kf.textgrammarcheck
    OLD_CATEGORY_NAMES org.kde.kf${KF_MAJOR_VERSION}.textgrammarcheck
        DESCRIPTION "KF${KF_MAJOR_VERSION} (Text Grammar Check)"
        EXPORT KTEXTADDONS
    )

target_sources(KF${KF_MAJOR_VERSION}TextGrammarCheck PRIVATE
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
if (BUILD_TESTING)
    add_subdirectory(grammalecte/autotests)
    add_subdirectory(grammalecte/tests)
    add_subdirectory(languagetool/autotests)
    add_subdirectory(languagetool/tests)
    add_subdirectory(common/autotests/)
endif()

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF${KF_MAJOR_VERSION}TextGrammarCheck PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KF${KF_MAJOR_VERSION}TextGrammarCheck BASE_NAME textgrammarcheck)


target_link_libraries(KF${KF_MAJOR_VERSION}TextGrammarCheck
    PUBLIC
    Qt::Gui
    Qt::Widgets
    PRIVATE
    Qt::Network
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::ConfigWidgets
    )

target_include_directories(KF${KF_MAJOR_VERSION}TextGrammarCheck INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextGrammarCheck/>")

set_target_properties(KF${KF_MAJOR_VERSION}TextGrammarCheck PROPERTIES
    VERSION ${TEXTGRAMMARCHECK_VERSION}
    SOVERSION ${TEXTGRAMMARCHECK_SOVERSION}
    EXPORT_NAME TextGrammarCheck
    )

install(TARGETS
    KF${KF_MAJOR_VERSION}TextGrammarCheck
    EXPORT KF${KF_MAJOR_VERSION}TextGrammarCheckTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
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


if (BUILD_QCH)
    ecm_add_qch(
        KF${KF_MAJOR_VERSION}TextGrammarCheck_QCH
        NAME KF${KF_MAJOR_VERSION}TextGrammarCheck
        BASE_NAME KF${KF_MAJOR_VERSION}TextGrammarCheck
        VERSION ${TEXTGRAMMARCHECK_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${TextGrammarCheck_common_HEADERS}
        ${TextGrammarCheck_grammalecte_HEADERS}
        ${TextGrammarCheck_languagetool_HEADERS}
        LINK_QCHS
            Qt${QT_MAJOR_VERSION}Core_QCH
            Qt${QT_MAJOR_VERSION}Gui_QCH
            Qt${QT_MAJOR_VERSION}Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            TEXTGRAMMARCHECK_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()
