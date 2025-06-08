# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

set(CMAKECONFIG_INSTALL_DIR
    "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF6TextAutoCorrectionWidgets"
)

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTAUTOCORRECTIONWIDGETS
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textautocorrectionwidgets_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoCorrectionWidgetsConfigVersion.cmake"
    SOVERSION 1
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoCorrectionWidgetsConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoCorrectionWidgetsConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(
    EXPORT KF6TextAutoCorrectionWidgetsTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KF6TextAutoCorrectionWidgetsTargets.cmake
    NAMESPACE KF6::
)

add_library(KF6TextAutoCorrectionWidgets)
add_library(KF6::TextAutoCorrectionWidgets ALIAS KF6TextAutoCorrectionWidgets)
ki18n_wrap_ui(KF6TextAutoCorrectionWidgets
    ui/autocorrectionwidget.ui
)
ecm_qt_declare_logging_category(KF6TextAutoCorrectionWidgets HEADER textautocorrectionautocorrectwidgets_debug.h
        IDENTIFIER TEXTAUTOCORRECTION_AUTOCORRECT_LOG
        CATEGORY_NAME org.kde.kf.textautocorrection.autocorrectwidgets
        OLD_CATEGORY_NAMES org.kde.kf6.textautocorrection.autocorrectwidgets
	DESCRIPTION "KF6 (AutoCorrection autocorrect text)"
	EXPORT KTEXTADDONS
)

target_sources(
    KF6TextAutoCorrectionWidgets
    PRIVATE
        autocorrectionwidget.cpp
        autocorrectionlistwidget.cpp
        autocorrectiontreewidget.cpp
        autocorrectionlanguage.cpp
        autocorrectionlistwidget.h
        autocorrectionlanguage.h
        autocorrectionwidget.h
        autocorrectiontreewidget.h
        autocorrectiontextedit.cpp
        autocorrectiontextedit.h
        autocorrectionlineedit.cpp
        autocorrectionlineedit.h
        autocorrectionlanguagemodel.h
        autocorrectionlanguagemodel.cpp
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        KF6TextAutoCorrectionWidgets
        PROPERTIES UNITY_BUILD ON
    )
endif()
generate_export_header(
    KF6TextAutoCorrectionWidgets
    BASE_NAME textautocorrectionwidgets
)

target_link_libraries(
    KF6TextAutoCorrectionWidgets
    PUBLIC KF6::TextAutoCorrectionCore Qt::Widgets
    PRIVATE KF6::I18n KF6::TextAddonsWidgets KF6::WidgetsAddons
)

target_include_directories(
    KF6TextAutoCorrectionWidgets
    INTERFACE
        "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrectionWidgets/>"
)

set_target_properties(
    KF6TextAutoCorrectionWidgets
    PROPERTIES
        VERSION ${TEXTAUTOCORRECTIONWIDGETS_VERSION}
        SOVERSION ${TEXTAUTOCORRECTIONWIDGETS_SOVERSION}
        EXPORT_NAME TextAutoCorrectionWidgets
)

install(
    TARGETS KF6TextAutoCorrectionWidgets
    EXPORT KF6TextAutoCorrectionWidgetsTargets
    ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
)

if(BUILD_TESTING)
    #add_subdirectory(autotests)
    add_subdirectory(tests)
endif()

ecm_generate_headers(TextAutoCorrection_Camelcaseautocorrectionwidgets_HEADERS
    HEADER_NAMES
    AutoCorrectionWidget
    AutoCorrectionLanguage
    AutoCorrectionTextEdit
    REQUIRED_HEADERS TextAutoCorrection_autocorrectionwidgets_HEADERS
    PREFIX TextAutoCorrectionWidgets
)

install(
    FILES ${TextAutoCorrection_Camelcaseautocorrectionwidgets_HEADERS}
    DESTINATION
        ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrectionWidgets/TextAutoCorrectionWidgets
    COMPONENT Devel
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/textautocorrectionwidgets_export.h
        ${TextAutoCorrection_autocorrectionwidgets_HEADERS}
    DESTINATION
        ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrectionWidgets/textautocorrectionwidgets
    COMPONENT Devel
)

if(BUILD_QCH)
    ecm_add_qch(
        KF6TextAutoCorrectionWidgets_QCH
        NAME KF6TextAutoCorrectionWidgets
        BASE_NAME KF6TextAutoCorrectionWidgets
        VERSION ${TEXTAUTOCORRECTIONWIDGETS_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${TextAutoCorrection_autocorrectionwidgets_HEADERS}
        LINK_QCHS
            Qt6Core_QCH
            Qt6Gui_QCH
            Qt6Widgets_QCH
        INCLUDE_DIRS
            ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
            TEXTAUTOCORRECTIONCORE_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()

if(BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF6TextAutoCorrectionWidgets_QCH
        FILE KF6TextAutoCorrectionWidgetsQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS
        "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF6TextAutoCorrectionWidgetsQchTargets.cmake\")"
    )
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextAutoCorrectionWidgetsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoCorrectionWidgetsConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

install(
    FILES ${CMAKE_CURRENT_BINARY_DIR}/textautocorrectionwidgets_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoCorrectionWidgets/
    COMPONENT Devel
)
