# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"libtextaddonswidgets\")

########### CMake Config Files ###########
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF6TextAddonsWidgets")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTADDONSWIDGETS
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textaddonswidgets_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAddonsWidgetsConfigVersion.cmake"
    SOVERSION 1
)

add_library(KF6TextAddonsWidgets)
add_library(KF6::TextAddonsWidgets ALIAS KF6TextAddonsWidgets)

target_sources(
    KF6TextAddonsWidgets
    PRIVATE
        selectspecialchardialog.h
        selectspecialchardialog.cpp
        slidecontainer.cpp
        slidecontainer.h
)
target_link_libraries(
    KF6TextAddonsWidgets
    PRIVATE
        Qt::Widgets
        KF6::WidgetsAddons
        KF6::ConfigGui
)

ecm_qt_declare_logging_category(KF6TextAddonsWidgets HEADER TextAddonsWidgets_debug.h
    IDENTIFIER TEXTADDONSWIDGETS_LOG
    CATEGORY_NAME org.kde.kf.textaddonswidgets
    OLD_CATEGORY_NAMES org.kde.kf6.textaddonswidgets
    DESCRIPTION "KF6 (textaddons widgets)" EXPORT KTEXTADDONS
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        KF6TextAddonsWidgets
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
generate_export_header(KF6TextAddonsWidgets BASE_NAME TextAddonsWidgets)

target_include_directories(
    KF6TextAddonsWidgets
    INTERFACE
        "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextAddonsWidgets;>"
)

target_link_libraries(KF6TextAddonsWidgets PRIVATE KF6::I18n)

set_target_properties(
    KF6TextAddonsWidgets
    PROPERTIES
        VERSION
            ${TEXTADDONSWIDGETS_VERSION}
        SOVERSION
            ${TEXTADDONSWIDGETS_SOVERSION}
        EXPORT_NAME
            TextAddonsWidgets
)

install(TARGETS KF6TextAddonsWidgets EXPORT KF6TextAddonsWidgetsTargets ${KDE_INSTALL_TARGETS_DEFAULT_ARGS})

ecm_generate_headers(TextAddonsWidgets_CamelCase_HEADERS
    HEADER_NAMES
    SelectSpecialCharDialog
    SlideContainer
    REQUIRED_HEADERS TextAddonsWidgets_HEADERS
    PREFIX TextAddonsWidgets
)

install(
    FILES
        ${TextAddonsWidgets_HEADERS}
        ${TextAddonsWidgets_lineedit_HEADERS}
        ${CMAKE_CURRENT_BINARY_DIR}/textaddonswidgets_export.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAddonsWidgets/textaddonswidgets
    COMPONENT Devel
)
install(
    FILES
        ${TextAddonsWidgets_CamelCase_HEADERS}
        ${TextAddonsWidgets_lineedit_CamelCase_HEADERS}
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAddonsWidgets/TextAddonsWidgets/
    COMPONENT Devel
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAddonsWidgetsConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAddonsWidgetsConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

install(
    EXPORT KF6TextAddonsWidgetsTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KF6TextAddonsWidgetsTargets.cmake
    NAMESPACE KF6::
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/textaddonswidgets_version.h
    DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAddonsWidgets
    COMPONENT Devel
)

if(BUILD_QCH)
    ecm_add_qch(
        KF6TextAddonsWidgets_QCH
        NAME KF6TextAddonsWidgets
        BASE_NAME KF6TextAddonsWidgets
        VERSION ${TEXTADDONSWIDGETS_VERSION}
        ORG_DOMAIN org.kde
        SOURCES # using only public headers, to cover only public API
        ${TextAddonsWidgets_HEADERS}
        LINK_QCHS
        Qt6Core_QCH
        Qt6Gui_QCH
        Qt6Widgets_QCH
        INCLUDE_DIRS
        ${CMAKE_CURRENT_BINARY_DIR}
        BLANK_MACROS
        TEXTADDONSWIDGETS_EXPORT
        TAGFILE_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        QCH_INSTALL_DESTINATION ${KDE_INSTALL_QTQCHDIR}
        COMPONENT Devel
    )
endif()

if(BUILD_QCH)
    ecm_install_qch_export(
        TARGETS KF6TextAddonsWidgets_QCH
        FILE KF6TextAddonsWidgetsQchTargets.cmake
        DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
        COMPONENT Devel
    )
    set(PACKAGE_INCLUDE_QCHTARGETS "include(\"\${CMAKE_CURRENT_LIST_DIR}/KF6TextAddonsWidgetsQchTargets.cmake\")")
endif()

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextAddonsWidgetsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAddonsWidgetsConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
    add_subdirectory(tests)
endif()
