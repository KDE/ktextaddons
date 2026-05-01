# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

macro(add_textautogenerate_mcpprotocol_widgets_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h TEST_NAME ${_name}
        NAME_PREFIX "textautogenerate-mcpprotocol-widgets-"
        LINK_LIBRARIES Qt::Test KF6::TextAutoGenerateTextMcpProtocolWidgets
    )
endmacro()
add_textautogenerate_mcpprotocol_widgets_unittest(textautogeneratetextmcpserverwidgettest.cpp)
add_textautogenerate_mcpprotocol_widgets_unittest(textautogenerateaddmcpserverwidgettest.cpp)
