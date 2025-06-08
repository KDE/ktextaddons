# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

macro(add_ollama_plugin_unittest _source)
    set(_test ${_source})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable(${_name} ${_test} ${_name}.h)
    add_test(NAME ${_name} COMMAND ${_name})

    ecm_mark_as_test(${_name})
    target_link_libraries(
        ${_name}
        Qt::Test
        KF6::TextAutoGenerateText
        textautogenerateollama
    )
    set_target_properties(${_name} PROPERTIES DISABLE_PRECOMPILE_HEADERS ON)
endmacro()

add_ollama_plugin_unittest(ollamautilstest.cpp)
add_ollama_plugin_unittest(ollamamodelavailableinfotest.cpp)
add_ollama_plugin_unittest(ollamamodelsavailableinfostest.cpp)
add_ollama_plugin_unittest(ollamamodellistviewtest.cpp)
add_ollama_plugin_unittest(ollamamodelavailblesearchwidgettest.cpp)
add_ollama_plugin_unittest(ollamamodelavailableinfossortproxymodeltest.cpp)
add_ollama_plugin_unittest(ollamamodelavailbleinfowidgettest.cpp)
add_ollama_plugin_unittest(ollamamodeldownloadwidgettest.cpp)
add_ollama_plugin_unittest(ollamamodeldownloadprogresswidgettest.cpp)
add_ollama_plugin_unittest(ollamamodelinstalledinfotest.cpp)
add_ollama_plugin_unittest(ollamamodelinstalledwidgettest.cpp)
add_ollama_plugin_unittest(ollamamodelsearchlineedittest.cpp)
add_ollama_plugin_unittest(ollamamodeldownloadfromnamewidgettest.cpp)
add_ollama_plugin_unittest(ollamamodeldownloadfromnamedialogtest.cpp)
add_ollama_plugin_unittest(ollamamodelinstalledinfowidgettest.cpp)
add_ollama_plugin_unittest(ollamamodelcreatewidgettest.cpp)
add_ollama_plugin_unittest(ollamamanagertest.cpp)
add_ollama_plugin_unittest(ollamamodelcreatefromexistingmodelwidgettest.cpp)
