# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

add_library(mcpprotocolserverplugin)

ecm_qt_declare_logging_category(mcpprotocolserverplugin
    HEADER autogeneratetext_mcpprotocolserverplugin_lib_debug.h
    IDENTIFIER AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LIB_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.mcpprotocolserverplugin_lib
    DESCRIPTION "autogenerate text mcpprotocol server plugin lib"
    EXPORT KTEXTADDONS
)

target_sources(
    mcpprotocolserverplugin
    PRIVATE
        sse/mcpserversse.h
        sse/mcpserversse.cpp
        sse/mcpserversseplugininterface.h
        sse/mcpserversseplugininterface.cpp
        stdio/mcpserverstdioplugininterface.cpp
        stdio/mcpserverstdioplugininterface.h
        stdio/mcpserverstdio.h
        stdio/mcpserverstdio.cpp
        streamanblehttp/mcpserverstreamblehttpplugininterface.h
        streamanblehttp/mcpserverstreamblehttpplugininterface.cpp
)

if(COMPILE_WITH_UNITY_CMAKE_SUPPORT)
    set_target_properties(
        mcpprotocolserverplugin
        PROPERTIES
            UNITY_BUILD
                ON
    )
endif()
generate_export_header(mcpprotocolserverplugin BASE_NAME mcpprotocolserverplugin)

target_link_libraries(
    mcpprotocolserverplugin
    PUBLIC
        KF6::TextAutoGenerateTextMcpProtocol
        Qt::Network
)
set_target_properties(
    mcpprotocolserverplugin
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
        mcpprotocolserverplugin
        ${KDE_INSTALL_TARGETS_DEFAULT_ARGS}
    LIBRARY
        NAMELINK_SKIP
)

######
add_library(autogeneratetext_mcpprotocolserverplugin MODULE)

ecm_qt_declare_logging_category(autogeneratetext_mcpprotocolserverplugin
    HEADER autogeneratetext_mcpprotocolserverplugin_debug.h
    IDENTIFIER AUTOGENERATETEXT_MCPPROTOCOLSERVER_PLUGIN_LOG
    CATEGORY_NAME org.kde.kf.autogeneratetext.mcpprotocolserverplugin
    DESCRIPTION "autogenerate text mcpprotocol server plugin"
    EXPORT KTEXTADDONS
)

target_sources(
    autogeneratetext_mcpprotocolserverplugin
    PRIVATE
        mcpserverplugin.h
        mcpserverplugin.cpp
)

target_link_libraries(
    autogeneratetext_mcpprotocolserverplugin
    PRIVATE
        KF6::TextAutoGenerateTextMcpProtocol
        mcpprotocolserverplugin
)
install(
    TARGETS
        autogeneratetext_mcpprotocolserverplugin
    DESTINATION ${KDE_INSTALL_PLUGINDIR}/kf6/textautogeneratetext/mcpprotocol
)
