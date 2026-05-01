# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF6TextAutoGenerateTextMcpProtocolWidgets")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetextmcpprotocolwidgets_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoGenerateTextMcpProtocolWidgetsConfigVersion.cmake"
    SOVERSION 1
)

add_library(KF6TextAutoGenerateTextMcpProtocolWidgets)

add_library(KF6::TextAutoGenerateTextMcpProtocolWidgets ALIAS KF6TextAutoGenerateTextMcpProtocolWidgets)

ecm_qt_declare_logging_category(KF6TextAutoGenerateTextMcpProtocolWidgets HEADER textautogeneratetextmcpprotocol_widgets_debug.h
    IDENTIFIER TEXTAUTOGENERATEMCPPROTOCOLWIDGETS_LOG
    CATEGORY_NAME org.kde.kf.TextAutoGenerateTextMcpProtocolWidgets
    DESCRIPTION "KF6 (TextAutoGenerateText widgets MCP protocols)"
    EXPORT KTEXTADDONS
)

target_sources(
    KF6TextAutoGenerateTextMcpProtocolWidgets
    PRIVATE
        addmcpprotocolclientwidget.h
        addmcpprotocolclientwidget.cpp
        addmcpprotocolclientdialog.h
        addmcpprotocolclientdialog.cpp
        server/addmcpserverdialog.cpp
        server/addmcpserverdialog.h
        server/addmcpserverwidget.cpp
        server/addmcpserverwidget.h
        server/mcpserverlistview.cpp
        server/mcpserverlistview.h
        server/mcpserverwidget.cpp
        server/mcpserverwidget.h
)

generate_export_header(KF6TextAutoGenerateTextMcpProtocolWidgets BASE_NAME textautogeneratetextmcpprotocolwidgets)

ecm_generate_headers(TextAutoGenerateTextMcpProtocolWidgets_Camelcasesmcpprotocolserver_HEADERS
    HEADER_NAMES
    AddMcpServerDialog
      McpServerWidget
    REQUIRED_HEADERS TextAutoGenerateTextMcpProtocolWidgets_mcpprotocolserver_HEADERS
    PREFIX TextAutoGenerateTextMcpProtocolWidgets
    RELATIVE server
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetextmcpprotocolwidgets_export.h
        ${TextAutoGenerateTextMcpProtocolWidgets_mcpprotocolserver_HEADERS}
    DESTINATION
        ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoGenerateTextMcpProtocolWidgets/textautogeneratetextmcpprotocolwidgets
    COMPONENT Devel
)

install(
    FILES
        ${TextAutoGenerateTextMcpProtocolWidgets_Camelcasesmcpprotocolserver_HEADERS}
    DESTINATION
        ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoGenerateTextMcpProtocolWidgets/TextAutoGenerateTextMcpProtocolWidgets
    COMPONENT Devel
)

target_link_libraries(
    KF6TextAutoGenerateTextMcpProtocolWidgets
    Qt::Widgets
    KF6::TextAutoGenerateTextMcpProtocolCore
    KF6::I18n
    KF6::WidgetsAddons
)

install(
    TARGETS
        KF6TextAutoGenerateTextMcpProtocolWidgets
    EXPORT KF6TextAutoGenerateTextMcpProtocolWidgetsTargets
    ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
)

install(
    EXPORT KF6TextAutoGenerateTextMcpProtocolWidgetsTargets
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    FILE KF6TextAutoGenerateTextMcpProtocolWidgetsTargets.cmake
    NAMESPACE KF6::
)

install(
    FILES
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoGenerateTextMcpProtocolWidgetsConfig.cmake"
        "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoGenerateTextMcpProtocolWidgetsConfigVersion.cmake"
    DESTINATION "${CMAKECONFIG_INSTALL_DIR}"
    COMPONENT Devel
)

configure_package_config_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/KFTextAutoGenerateTextMcpProtocolWidgetsConfig.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoGenerateTextMcpProtocolWidgetsConfig.cmake"
    INSTALL_DESTINATION ${CMAKECONFIG_INSTALL_DIR}
)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
