# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

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
        addmcpserverdialog.cpp
        addmcpserverdialog.h
        addmcpserverwidget.cpp
        addmcpserverwidget.h
        mcpserverlistview.cpp
        mcpserverlistview.h
        mcpserverwidget.cpp
        mcpserverwidget.h
)

generate_export_header(KF6TextAutoGenerateTextMcpProtocolWidgets BASE_NAME textautogeneratetextmcpprotocolwidgets)

# ecm_generate_headers(TextAutoGenerateTextMcpProtocol_Camelcasesmcpprotocolcommon_HEADERS
#     HEADER_NAMES
#     REQUIRED_HEADERS TextAutoGenerateTextMcpProtocol_mcpprotocolcommon_HEADERS
#     PREFIX TextAutoGenerateTextMcpProtocol
#     RELATIVE common
# )

# ecm_generate_headers(TextAutoGenerateTextMcpProtocol_Camelcasesmcpprotocolclient_HEADERS
#     HEADER_NAMES
#     McpProtocolClient
#     REQUIRED_HEADERS TextAutoGenerateTextMcpProtocol_mcpprotocolclient_HEADERS
#     PREFIX TextAutoGenerateTextMcpProtocol
#     RELATIVE client
# )

# ecm_generate_headers(TextAutoGenerateTextMcpProtocol_Camelcasesmcpprotocolserver_HEADERS
#     HEADER_NAMES
#     McpProtocolServer
#     REQUIRED_HEADERS TextAutoGenerateTextMcpProtocol_mcpprotocolserver_HEADERS
#     PREFIX TextAutoGenerateTextMcpProtocol
#     RELATIVE server
# )

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetextmcpprotocolwidgets_export.h
    DESTINATION
        ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoGenerateTextMcpProtocolWidgets/TextAutoGenerateTextMcpProtocolWidgets
    COMPONENT Devel
)

# install(
#     FILES
#     DESTINATION ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoGenerateTextMcpProtocolWidgets/TextAutoGenerateTextMcpProtocolWidgets
#     COMPONENT Devel
# )

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
if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
