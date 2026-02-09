# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

macro(add_ollamacommon_plugin_unittest _source)
    set(_test ${_source})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable(
        ${_name}
        ${_test}
        ${_name}.h
    )
    add_test(NAME ${_name} COMMAND ${_name})

    ecm_mark_as_test(${_name})
    target_link_libraries(
        ${_name}
        Qt::Test
        textautogenerateollamacommon
    )
    set_target_properties(
        ${_name}
        PROPERTIES
            DISABLE_PRECOMPILE_HEADERS
                ON
    )
endmacro()

add_ollamacommon_plugin_unittest(ollamacommonutilstest.cpp)
add_ollamacommon_plugin_unittest(ollamacommonmodelavailableinfotest.cpp)
add_ollamacommon_plugin_unittest(ollamacommonmodelsavailableinfostest.cpp)
add_ollamacommon_plugin_unittest(ollamacommonmodelavailableinfossortproxymodeltest.cpp)
