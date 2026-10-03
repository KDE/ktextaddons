# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

macro(add_textautogenerate_mcpprotocol_client_plugin_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h fakemcphttpserver.h fakemcphttpserver.cpp TEST_NAME ${_name}
        NAME_PREFIX "textautogenerate-mcpprotocol-clientplugin-"
        LINK_LIBRARIES Qt::Test Qt::Network mcpprotocolclientplugin KF6::TextAutoGenerateTextMcpProtocolCore
    )
endmacro()

add_textautogenerate_mcpprotocol_client_plugin_unittest(mcpclientstreamablehttptest.cpp)
add_textautogenerate_mcpprotocol_client_plugin_unittest(mcpclientssetest.cpp)
add_textautogenerate_mcpprotocol_client_plugin_unittest(mcpclientstdiotest.cpp)
