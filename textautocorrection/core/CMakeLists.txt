# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: none


set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF${KF_MAJOR_VERSION}TextAutoCorrection")



ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTAUTOCORRECTION
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textautocorrection_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextAutoCorrectionConfigVersion.cmake"
    SOVERSION 1
    )

install(FILES
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextAutoCorrectionConfig.cmake"
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextAutoCorrectionConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KF${KF_MAJOR_VERSION}TextAutoCorrectionTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF${KF_MAJOR_VERSION}TextAutoCorrectionTargets.cmake NAMESPACE KF${KF_MAJOR_VERSION}::)

kconfig_add_kcfg_files(textautocorrection_settings_SRCS
    settings/textautocorrectionsetting_base.kcfgc
    )

add_library(KF${KF_MAJOR_VERSION}TextAutoCorrection )
add_library(KF${KF_MAJOR_VERSION}::TextAutoCorrection ALIAS KF${KF_MAJOR_VERSION}TextAutoCorrection)
ki18n_wrap_ui(KF${KF_MAJOR_VERSION}TextAutoCorrection
    ui/autocorrectionwidget.ui
    )
ecm_qt_declare_logging_category(KF${KF_MAJOR_VERSION}TextAutoCorrection HEADER textautocorrection_debug.h
        IDENTIFIER TEXTAUTOCORRECTION_LOG CATEGORY_NAME org.kde.kf${KF_MAJOR_VERSION}.textautocorrection
	DESCRIPTION "KF${KF_MAJOR_VERSION} (text AutoCorrection)"
	EXPORT KTEXTADDONS
    )

ecm_qt_declare_logging_category(KF${KF_MAJOR_VERSION}TextAutoCorrection HEADER textautocorrectionautocorrect_debug.h
        IDENTIFIER TEXTAUTOCORRECTION_AUTOCORRECT_LOG CATEGORY_NAME org.kde.kf${KF_MAJOR_VERSION}.textautocorrection.autocorrect
	DESCRIPTION "KF${KF_MAJOR_VERSION} (AutoCorrection autocorrect text)"
	EXPORT KTEXTADDONS
    )

target_sources(KF${KF_MAJOR_VERSION}TextAutoCorrection PRIVATE
    ${textautocorrection_settings_SRCS}
    autocorrection.cpp
    autocorrection.h
    autocorrectionutils.h
    autocorrectionutils.cpp
    autocorrectionsettings.h
    autocorrectionsettings.cpp

    import/importlibreofficeautocorrection.cpp
    import/importkmailautocorrection.cpp
    import/importabstractautocorrection.cpp
    import/importkmailautocorrection.h
    import/importlibreofficeautocorrection.h
    import/importabstractautocorrection.h

    export/exportabstractautocorrection.h
    export/exportabstractautocorrection.cpp
    export/exportlibreofficeautocorrection.h
    export/exportlibreofficeautocorrection.cpp

    settings/textautocorrectionsettings.h
    settings/textautocorrectionsettings.cpp

    )

target_sources(KF${KF_MAJOR_VERSION}TextAutoCorrection PRIVATE
    widgets/autocorrectionwidget.cpp
    widgets/autocorrectionlistwidget.cpp
    widgets/autocorrectiontreewidget.cpp
    widgets/autocorrectionlanguage.cpp
    widgets/autocorrectionlistwidget.h
    widgets/autocorrectionlanguage.h
    widgets/autocorrectionwidget.h
    widgets/autocorrectiontreewidget.h
    widgets/selectspecialchardialog.h
    widgets/selectspecialchardialog.cpp
    widgets/autocorrectiontextedit.cpp
    widgets/autocorrectiontextedit.h
    widgets/autocorrectionlineedit.cpp
    widgets/autocorrectionlineedit.h
)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(KF${KF_MAJOR_VERSION}TextAutoCorrection PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KF${KF_MAJOR_VERSION}TextAutoCorrection BASE_NAME textautocorrection)


target_link_libraries(KF${KF_MAJOR_VERSION}TextAutoCorrection
    PUBLIC
    Qt::Gui
    Qt::Widgets
    KF${KF_MAJOR_VERSION}::ConfigWidgets
    PRIVATE
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::Archive
    KF${KF_MAJOR_VERSION}::TextAddonsWidgets
    Qt::Xml
    )

target_include_directories(KF${KF_MAJOR_VERSION}TextAutoCorrection INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrection/>")

set_target_properties(KF${KF_MAJOR_VERSION}TextAutoCorrection PROPERTIES
    VERSION ${TEXTAUTOCORRECTION_VERSION}
    SOVERSION ${TEXTAUTOCORRECTION_SOVERSION}
    EXPORT_NAME TextAutoCorrection
    )

install(TARGETS
    KF${KF_MAJOR_VERSION}TextAutoCorrection
    EXPORT KF${KF_MAJOR_VERSION}TextAutoCorrectionTargets ${KF_INSTALL_TARGETS_DEFAULT_ARGS}
    )

if (BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()


ecm_generate_headers(TextAutoCorrection_Camelcaseautocorrectionwidgets_HEADERS
    HEADER_NAMES
    AutoCorrectionWidget
    AutoCorrectionLanguage
    SelectSpecialCharDialog
    AutoCorrectionTextEdit
    REQUIRED_HEADERS TextAutoCorrection_autocorrectionwidgets_HEADERS
    PREFIX TextAutoCorrection
    RELATIVE widgets/
    )

ecm_generate_headers(TextAutoCorrection_Camelcaseautocorrection_HEADERS
    HEADER_NAMES
    AutoCorrection
    AutoCorrectionSettings
    AutoCorrectionUtils

    REQUIRED_HEADERS TextAutoCorrection_autocorrection_HEADERS
    PREFIX TextAutoCorrection
    )

ecm_generate_headers(TextAutoCorrection_Camelcasesettings_HEADERS
    HEADER_NAMES
    TextAutoCorrectionSettings
    REQUIRED_HEADERS TextAutoCorrection_settings_HEADERS
    PREFIX TextAutoCorrection
    RELATIVE settings
    )

ecm_generate_pri_file(BASE_NAME TextAutoCorrection
    LIB_NAME KF${KF_MAJOR_VERSION}TextAutoCorrection
    DEPS "KConfigWidgets" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrection
    )


install(FILES
    ${TextAutoCorrection_Camelcaseautocorrection_HEADERS}
    ${TextAutoCorrection_Camelcaseautocorrectionwidgets_HEADERS}
    ${TextAutoCorrection_Camelcasesettings_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrection/TextAutoCorrection
    COMPONENT Devel
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textautocorrection_export.h
    ${CMAKE_CURRENT_BINARY_DIR}/textautocorrectionsetting_base.h
    ${TextAutoCorrection_autocorrection_HEADERS}
    ${TextAutoCorrection_autocorrectionwidgets_HEADERS}
    ${TextAutoCorrection_settings_HEADERS}

    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrection/textautocorrection
    COMPONENT Devel
    )

install(FILES
    ${PRI_FILENAME}
    DESTINATION ${ECM_MKSPECS_INSTALL_DIR})


if (BUILD_QCH)
    ecm_add_qch(
        KF${KF_MAJOR_VERSION}TextAutoCorrection_QCH
        NAME KF${KF_MAJOR_VERSION}TextAutoCorrection
        BASE_NAME KF${KF_MAJOR_VERSION}TextAutoCorrection
        VERSION ${TEXTAUTOCORRECTION_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${TextAutoCorrection_autocorrection_HEADERS}
        ${TextAutoCorrection_autocorrectionwidgets_HEADERS}
        ${TextAutoCorrection_settings_HEADERS}
        LINK_QCHS
            Qt${QT_MAJOR_VERSION}Core_QCH
            Qt${QT_MAJOR_VERSION}Gui_QCH
            Qt${QT_MAJOR_VERSION}Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            TEXTAUTOCORRECTION_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()

if (BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF${KF_MAJOR_VERSION}TextAutoCorrection_QCH
        FILE KF${KF_MAJOR_VERSION}TextAutoCorrectionQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF${KF_MAJOR_VERSION}TextAutoCorrectionQchTargets.cmake\")")
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextAutoCorrectionConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextAutoCorrectionConfig.cmake"
    INSTALL_DESTINATION  ${CMAKECONFIG_INSTALL_DIR}
    )


install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textautocorrection_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrection/ COMPONENT Devel
    )
