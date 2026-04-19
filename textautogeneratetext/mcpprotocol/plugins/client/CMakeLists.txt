# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

add_library(mcpprotocolclientplugin)

ecm_qt_declare_logging_category(mcpprotocolclientplugin
    HEADER autogeneratetext_mcpprotocolclientplugin_lib_debug.h
    IDENTIFIER AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.mcpprotocolclientplugin_lib
    DESCRIPTION "autogenerate text mcpprotocol client plugin lib"
    EXPORT KTEXTADDONS
)

target_sources(
    mcpprotocolclientplugin
    PRIVATE
        sse/mcpclientsse.h
        sse/mcpclientsse.cpp
        sse/mcpclientsseplugininterface.h
        sse/mcpclientsseplugininterface.cpp
        stdio/mcpclientstdioplugininterface.cpp
        stdio/mcpclientstdioplugininterface.h
        stdio/mcpclientstdio.h
        stdio/mcpclientstdio.cpp
        streamanblehttp/mcpclientstreamblehttpplugininterface.h
        streamanblehttp/mcpclientstreamblehttpplugininterface.cpp
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        mcpprotocolclientplugin
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
generate_export_header(mcpprotocolclientplugin BASE_NAME mcpprotocolclientplugin)

target_link_libraries(
    mcpprotocolclientplugin
    PUBLIC
        KF6::TextAutoGenerateTextMcpProtocol
        Qt::Network
)
set_target_properties(
    mcpprotocolclientplugin
    PROPERTIES
        VERSION
            ${TEXTAUTOGENERATETEXT_VERSION}
        SOVERSION
            ${TEXTAUTOGENERATETEXT_SOVERSION}
        EXPORT_NAME
            TextAutoGenerateText
)

install(
    TARGETS
        mcpprotocolclientplugin
        ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    LIBRARY
        NAMELINK_SKIP
)

######
kcoreaddons_add_plugin(autogeneratetext_mcpprotocolclientplugin INSTALL_NAMESPACE kf6/textautogeneratetext/mcpprotocol)
ecm_qt_declare_logging_category(autogeneratetext_mcpprotocolclientplugin
    HEADER autogeneratetext_mcpprotocolclientplugin_debug.h
    IDENTIFIER AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.mcpprotocolclientplugin
    DESCRIPTION "autogenerate text mcpprotocol client plugin"
    EXPORT KTEXTADDONS
)

target_sources(
    autogeneratetext_mcpprotocolclientplugin
    PRIVATE
        mcpclientplugin.h
        mcpclientplugin.cpp
)

target_link_libraries(
    autogeneratetext_mcpprotocolclientplugin
    PRIVATE
        KF6::TextAutoGenerateTextMcpProtocol
        mcpprotocolclientplugin
)
