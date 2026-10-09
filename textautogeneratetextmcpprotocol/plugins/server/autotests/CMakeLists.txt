# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

macro(add_textautogenerate_mcpprotocol_server_plugin_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h TEST_NAME ${_name}
        NAME_PREFIX "textautogenerate-mcpprotocol-serverplugin-"
        LINK_LIBRARIES Qt::Test Qt::Network mcpprotocolserverplugin mcpprotocolclientplugin KF6::TextAutoGenerateTextMcpProtocolCore
    )
endmacro()

add_textautogenerate_mcpprotocol_server_plugin_unittest(mcpserverstreamablehttptest.cpp)

# Stdio server launched by mcpserverstdiotest
add_executable(mcpserverstdiohelper mcpserverstdiohelper.cpp)
target_link_libraries(mcpserverstdiohelper KF6::TextAutoGenerateTextMcpProtocolCore)

add_textautogenerate_mcpprotocol_server_plugin_unittest(mcpserverstdiotest.cpp)
target_compile_definitions(mcpserverstdiotest PRIVATE MCPSERVERSTDIOHELPER_PATH="$<TARGET_FILE:mcpserverstdiohelper>")
add_dependencies(
    mcpserverstdiotest
    mcpserverstdiohelper
    autogeneratetext_mcpprotocolserverplugin
)
