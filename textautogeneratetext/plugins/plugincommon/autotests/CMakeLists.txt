# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
# SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

macro(add_plugincommon_plugin_unittest _source)
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
        textautogenerateplugincommon
    )
    set_target_properties(
        ${_name}
        PROPERTIES
            DISABLE_PRECOMPILE_HEADERS
                ON
    )
endmacro()

add_plugincommon_plugin_unittest(plugincommonmodelinstalledinfossortproxymodeltest.cpp)
add_plugincommon_plugin_unittest(plugincommonmodelinstalledinfotest.cpp)
