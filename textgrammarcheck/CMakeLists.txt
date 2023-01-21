# SPDX-License-Identifier: CC0-1.0
# SPDX-FileCopyrightText: none

add_definitions(-DTRANSLATION_DOMAIN=\"libtextgrammarcheck\")

set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF5TextGrammarCheck")

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KF5TextGrammarCheckConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5TextGrammarCheckConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )


ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTGRAMMARCHECK
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textgrammarcheck_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF5TextGrammarCheckConfigVersion.cmake"
    SOVERSION 1
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF5TextGrammarCheckConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF5TextGrammarCheckConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KF5TextGrammarCheckTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF5TextGrammarCheckTargets.cmake NAMESPACE KF5::)

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textgrammarcheck_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextGrammarCheck/ COMPONENT Devel
    )

add_library(KF5TextGrammarCheck )
add_library(KF${KF_MAJOR_VERSION}::TextGrammarCheck ALIAS KF5TextGrammarCheck)
ecm_qt_declare_logging_category(KF5TextGrammarCheck HEADER textgrammarcheck_debug.h
    IDENTIFIER TEXTGRAMMARCHECK_LOG CATEGORY_NAME org.kde.kf5.textgrammarcheck
        DESCRIPTION "kf5 (Text Grammar Check)"
        EXPORT KTEXTADDONS
    )

target_sources(KF5TextGrammarCheck PRIVATE
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
    set_target_properties(KF5TextGrammarCheck PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KF5TextGrammarCheck BASE_NAME textgrammarcheck)


target_link_libraries(KF5TextGrammarCheck
    PUBLIC
    Qt::Gui
    Qt::Widgets
    PRIVATE
    Qt::Network
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::ConfigWidgets
    )

target_include_directories(KF5TextGrammarCheck INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextGrammarCheck/>")

set_target_properties(KF5TextGrammarCheck PROPERTIES
    VERSION ${TEXTGRAMMARCHECK_VERSION}
    SOVERSION ${TEXTGRAMMARCHECK_SOVERSION}
    EXPORT_NAME TextGrammarCheck
    )

install(TARGETS
    KF5TextGrammarCheck
    EXPORT KF5TextGrammarCheckTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS}
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


ecm_generate_pri_file(BASE_NAME TextGrammarCheck
    LIB_NAME KF5TextGrammarCheck
    DEPS "" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF}/TextGrammarCheck
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

install(FILES
    ${PRI_FILENAME}
    DESTINATION ${ECM_MKSPECS_INSTALL_DIR})


if (BUILD_QCH)
    ecm_add_qch(
        KF5TextGrammarCheck_QCH
        NAME KF5TextGrammarCheck
        BASE_NAME KF5TextGrammarCheck
        VERSION ${TEXTGRAMMARCHECK_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${TextGrammarCheck_common_HEADERS}
        ${TextGrammarCheck_grammalecte_HEADERS}
        ${TextGrammarCheck_languagetool_HEADERS}
        LINK_QCHS
            Qt5Core_QCH
            Qt5Gui_QCH
            Qt5Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            TEXTGRAMMARCHECK_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
    ecm_install_qch_export(
        TARGETS KF5TextGrammarCheck_QCH
        FILE KF5TextGrammarCheckQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF5TextGrammarCheckQchTargets.cmake\")")
endif()
