# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: none


set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF${KF_MAJOR_VERSION}TextAutoCorrectionWidgets")



ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTAUTOCORRECTIONWIDGETS
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textautocorrectionwidgets_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextAutoCorrectionWidgetsConfigVersion.cmake"
    SOVERSION 1
    )

install(FILES
	"${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextAutoCorrectionWidgetsConfig.cmake"
	"${CMAKE_CURRENT_BINARY_DIR}/KF${KF_MAJOR_VERSION}TextAutoCorrectionWidgetsConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
    )

install(EXPORT KF${KF_MAJOR_VERSION}TextAutoCorrectionWidgetsTargets DESTINATION "${CMAKECONFIG_INSTALL_DIR}" FILE KF${KF_MAJOR_VERSION}TextAutoCorrectionWidgetsTargets.cmake NAMESPACE KF${KF_MAJOR_VERSION}::)

kconfig_add_kcfg_files(textautocorrection_settings_SRCS
    settings/textautocorrectionsetting_base.kcfgc
    )

add_library(KF${KF_MAJOR_VERSION}TextAutoCorrectionWidgets )
add_library(KF${KF_MAJOR_VERSION}::TextAutoCorrectionWigdgets ALIAS KF${KF_MAJOR_VERSION}TextAutoCorrectionWidgets)
ki18n_wrap_ui(KF${KF_MAJOR_VERSION}TextAutoCorrectionWidgets
    widgets/ui/autocorrectionwidget.ui
    )
ecm_qt_declare_logging_category(KF${KF_MAJOR_VERSION}TextAutoCorrectionWidgets HEADER textautocorrectionautocorrectwidgets_debug.h
        IDENTIFIER TEXTAUTOCORRECTION_AUTOCORRECT_LOG CATEGORY_NAME org.kde.kf${KF_MAJOR_VERSION}.textautocorrection.autocorrectwidgets
	DESCRIPTION "KF${KF_MAJOR_VERSION} (AutoCorrection autocorrect text)"
	EXPORT KTEXTADDONS
    )

target_sources(KF${KF_MAJOR_VERSION}TextAutoCorrectionWidgets PRIVATE
    autocorrectionwidget.cpp
    autocorrectionlistwidget.cpp
    autocorrectiontreewidget.cpp
    autocorrectionlanguage.cpp
    autocorrectionlistwidget.h
    autocorrectionlanguage.h
    autocorrectionwidget.h
    autocorrectiontreewidget.h
    selectspecialchardialog.h
    selectspecialchardialog.cpp
    autocorrectiontextedit.cpp
    autocorrectiontextedit.h
    autocorrectionlineedit.cpp
    autocorrectionlineedit.h
)

if (COMPILE_WITH_UNITY_CMAKE_SUPPORT)
	set_target_properties(KF${KF_MAJOR_VERSION}TextAutoCorrectionWidgets PROPERTIES UNITY_BUILD ON)
endif()
generate_export_header(KF${KF_MAJOR_VERSION}TextAutoCorrectionWidgets BASE_NAME textautocorrectionwidgets)


target_link_libraries(KF${KF_MAJOR_VERSION}TextAutoCorrectionWidgets
    PUBLIC
    Qt::Gui
    Qt::Widgets
    KF${KF_MAJOR_VERSION}::ConfigWidgets
    PRIVATE
    KF${KF_MAJOR_VERSION}::I18n
    KF${KF_MAJOR_VERSION}::TextAddonsWidgets
    )

target_include_directories(KF${KF_MAJOR_VERSION}TextAutoCorrectionWidgets INTERFACE "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrectionWidgets/>")

set_target_properties(KF${KF_MAJOR_VERSION}TextAutoCorrectionWidgets PROPERTIES
	VERSION ${TEXTAUTOCORRECTIONWIDGETS_VERSION}
	SOVERSION ${TEXTAUTOCORRECTIONWIDGETS_SOVERSION}
    EXPORT_NAME TextAutoCorrectionWidgets
    )

install(TARGETS
	KF${KF_MAJOR_VERSION}TextAutoCorrectionWidgets
	EXPORT KF${KF_MAJOR_VERSION}TextAutoCorrectionWidgetsTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    )

if (BUILD_TESTING)
	#add_subdirectory(autotests)
    add_subdirectory(tests)
endif()


ecm_generate_headers(TextAutoCorrection_Camelcaseautocorrectionwidgets_HEADERS
    HEADER_NAMES
    AutoCorrectionWidget
    AutoCorrectionLanguage
    SelectSpecialCharDialog
    AutoCorrectionTextEdit
    REQUIRED_HEADERS TextAutoCorrection_autocorrectionwidgets_HEADERS
    PREFIX TextAutoCorrectionWidgets
    )

ecm_generate_pri_file(BASE_NAME TextAutoCorrectionWidgets
	LIB_NAME KF${KF_MAJOR_VERSION}TextAutoCorrectionWidgets
	DEPS "" FILENAME_VAR PRI_FILENAME INCLUDE_INSTALL_DIR ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrectionWidgets
    )


install(FILES
    ${TextAutoCorrection_Camelcaseautocorrectionwidgets_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrectionWidgets/TextAutoCorrectionWidgets
    COMPONENT Devel
    )

install(FILES
    ${CMAKE_CURRENT_BINARY_DIR}/textautocorrection_export.h
    ${TextAutoCorrection_autocorrectionwidgets_HEADERS}

    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrectionWidgets/textautocorrectionwidgets
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
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrectionWidgets/ COMPONENT Devel
    )
