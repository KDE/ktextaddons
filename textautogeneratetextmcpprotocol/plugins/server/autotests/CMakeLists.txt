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
