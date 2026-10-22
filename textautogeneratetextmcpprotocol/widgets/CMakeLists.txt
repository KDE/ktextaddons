# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
set(CMAKECONFIG_INSTALL_DIR "${KDE_INSTALL_CMAKEPACKAGEDIR}/KF6TextAutoGenerateTextMcpProtocolWidgets")

ecm_setup_version(PROJECT VARIABLE_PREFIX TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS
    VERSION_HEADER "${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetextmcpprotocolwidgets_version.h"
    PACKAGE_VERSION_FILE "${CMAKE_CURRENT_BINARY_DIR}/KF6TextAutoGenerateTextMcpProtocolWidgetsConfigVersion.cmake"
    SOVERSION 1
)

add_library(
    KF6TextAutoGenerateTextMcpProtocolWidgets
    server/mcpprotocolserverconfiguretokenwidget.h
    server/mcpprotocolserverconfiguretokenwidget.cpp
    client/addmcpregistryserverwidget.h
    client/addmcpregistryserverwidget.cpp
)

add_library(KF6::TextAutoGenerateTextMcpProtocolWidgets ALIAS KF6TextAutoGenerateTextMcpProtocolWidgets)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        KF6TextAutoGenerateTextMcpProtocolWidgets
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()

ecm_qt_declare_logging_category(KF6TextAutoGenerateTextMcpProtocolWidgets HEADER textautogeneratetextmcpprotocol_widgets_debug.h
    IDENTIFIER TEXTAUTOGENERATEMCPPROTOCOLWIDGETS_LOG
    CATEGORY_NAME org.kde.kf.TextAutoGenerateTextMcpProtocolWidgets
    DESCRIPTION "KF6 (TextAutoGenerateText widgets MCP protocols)"
    EXPORT KTEXTADDONS
)

target_sources(
    KF6TextAutoGenerateTextMcpProtocolWidgets
    PRIVATE
        server/mcpprotocolserverconfigurewidget.h
        server/mcpprotocolserverconfigurewidget.cpp
        server/mcpprotocolserverconfiguredialog.h
        server/mcpprotocolserverconfiguredialog.cpp
        client/addmcpserverdialog.cpp
        client/addmcpserverdialog.h
        client/addmcpserverwidget.cpp
        client/addmcpserverwidget.h
        client/mcpserverlistview.cpp
        client/mcpserverlistview.h
        client/mcpserverwidget.cpp
        client/mcpserverwidget.h
        client/addmcpstdioserverwidget.h
        client/addmcpstdioserverwidget.cpp
        client/addmcpsseserverwidget.cpp
        client/addmcpsseserverwidget.h
        client/addmcpstreamablehttpserverwidget.cpp
        client/addmcpstreamablehttpserverwidget.h
        client/addmcpserverbasewidget.h
        client/addmcpserverrootswidget.h
        client/addmcpserverrootswidget.cpp
        client/addmcpserverbasewidget.cpp
        client/mcpserverlistviewdelegate.h
        client/mcpserverlistviewdelegate.cpp
        client/mcpserversortfilterproxymodel.h
        client/mcpserversortfilterproxymodel.cpp
        client/addmcpstreamablehttpserverheaderwidget.h
        client/addmcpstreamablehttpserverheaderwidget.cpp
        client/addmcpstreamablehttpserverheaderlistwidget.h
        client/addmcpstreamablehttpserverheaderlistwidget.cpp
        client/addmcpstreamablehttpserverheaderconfiguredialog.h
        client/addmcpstreamablehttpserverheaderconfiguredialog.cpp
        client/addmcpstreamablehttpserverheaderconfigurewidget.h
        client/addmcpstreamablehttpserverheaderconfigurewidget.cpp
        common/selecttypecombobox.h
        common/selecttypecombobox.cpp
)

target_include_directories(
    KF6TextAutoGenerateTextMcpProtocolWidgets
    INTERFACE
        "$<INSTALL_INTERFACE:${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoGenerateTextMcpProtocolWidgets;>"
)
generate_export_header(KF6TextAutoGenerateTextMcpProtocolWidgets BASE_NAME textautogeneratetextmcpprotocolwidgets)

ecm_generate_headers(TextAutoGenerateTextMcpProtocolWidgets_Camelcasesmcpprotocolclient_HEADERS
    HEADER_NAMES
    AddMcpServerDialog
    McpServerWidget
    AddMcpServerWidget
    McpServerListView
    REQUIRED_HEADERS TextAutoGenerateTextMcpProtocolWidgets_mcpprotocolclient_HEADERS
    PREFIX TextAutoGenerateTextMcpProtocolWidgets
    RELATIVE client
)

ecm_generate_headers(TextAutoGenerateTextMcpProtocolWidgets_Camelcasesmcpprotocolserver_HEADERS
    HEADER_NAMES
        McpProtocolServerConfigureWidget
        McpProtocolServerConfigureDialog
    REQUIRED_HEADERS TextAutoGenerateTextMcpProtocolWidgets_mcpprotocolserver_HEADERS
    PREFIX TextAutoGenerateTextMcpProtocolWidgets
    RELATIVE server
)

install(
    FILES
        ${CMAKE_CURRENT_BINARY_DIR}/textautogeneratetextmcpprotocolwidgets_export.h
        ${TextAutoGenerateTextMcpProtocolWidgets_mcpprotocolclient_HEADERS}
        ${TextAutoGenerateTextMcpProtocolWidgets_mcpprotocolserver_HEADERS}
    DESTINATION
        ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoGenerateTextMcpProtocolWidgets/textautogeneratetextmcpprotocolwidgets
    COMPONENT Devel
)

install(
    FILES
        ${TextAutoGenerateTextMcpProtocolWidgets_Camelcasesmcpprotocolserver_HEADERS}
        ${TextAutoGenerateTextMcpProtocolWidgets_Camelcasesmcpprotocolclient_HEADERS}
    DESTINATION
        ${KDE_INSTALL_INCLUDEDIR_KF}/TextAutoGenerateTextMcpProtocolWidgets/TextAutoGenerateTextMcpProtocolWidgets
    COMPONENT Devel
)

target_link_libraries(
    KF6TextAutoGenerateTextMcpProtocolWidgets
    PUBLIC
        Qt::Widgets
        KF6::TextAutoGenerateTextMcpProtocolCore
    PRIVATE
        KF6::I18n
        KF6::WidgetsAddons
        KF6::IconWidgets
        KF6::TextAddonsWidgets
)

set_target_properties(
    KF6TextAutoGenerateTextMcpProtocolWidgets
    PROPERTIES
        VERSION
            ${TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_VERSION}
        SOVERSION
            ${TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_SOVERSION}
        EXPORT_NAME
            TextAutoGenerateTextMcpProtocolWidgets
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

ecm_add_installed_library_check(KF6TextAutoGenerateTextMcpProtocolWidgets
    PACKAGE_NAME "KF6TextAutoGenerateTextMcpProtocolWidgets"
    PACKAGE_VERSION ${TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_VERSION}
    PACKAGE_TARGET_NAMESPACE "KF6::"
)

ecm_installed_library_check_include_strings(KF6TextAutoGenerateTextMcpProtocolWidgets
    HEADERS
    ${TextAutoGenerateTextMcpProtocolWidgets_mcpprotocolclient_HEADERS}
    PREFIX textautogeneratetextmcpprotocolwidgets
)

ecm_installed_library_check_include_strings(KF6TextAutoGenerateTextMcpProtocolWidgets
    HEADERS
    ${TextAutoGenerateTextMcpProtocolWidgets_Camelcasesmcpprotocolclient_HEADERS}
        ${TextAutoGenerateTextMcpProtocolWidgets_Camelcasesmcpprotocolserver_HEADERS}
    PREFIX TextAutoGenerateTextMcpProtocolWidgets
)
