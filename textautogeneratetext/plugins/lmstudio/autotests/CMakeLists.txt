# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
# SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

macro(add_lmstudio_plugin_unittest _source)
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
        KF6::TextAutoGenerateText
        KF6::KIOWidgets
        textautogeneratelmstudio
    )
    set_target_properties(
        ${_name}
        PROPERTIES
            DISABLE_PRECOMPILE_HEADERS
                ON
    )
endmacro()

add_lmstudio_plugin_unittest(lmstudiomodelinstalledinfotest.cpp)
add_lmstudio_plugin_unittest(lmstudiocommonutilstest.cpp)
