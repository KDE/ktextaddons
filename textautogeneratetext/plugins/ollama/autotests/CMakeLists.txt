# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

macro(add_ollama_plugin_unittest _source)
    set(_test ${_source}  ${_additional})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable(${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name} )

    ecm_mark_as_test(${_name})
    target_link_libraries(${_name} Qt::Test KF6::TextAutoGenerateText textautogenerateollama)
    set_target_properties(${_name} PROPERTIES DISABLE_PRECOMPILE_HEADERS ON)
endmacro()

add_ollama_plugin_unittest(ollamautilstest.cpp)
add_ollama_plugin_unittest(ollamamodelinfotest.cpp)
