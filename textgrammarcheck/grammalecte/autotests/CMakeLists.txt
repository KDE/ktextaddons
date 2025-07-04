# SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_definitions(-DGRAMMALECTE_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data")

macro(add_grammalecte_unittest _source)
    set(_test ${_source})
    get_filename_component(_name ${_source} NAME_WE)
    add_executable(
        ${_name}
        ${_test}
        ${_name}.h
    )
    add_test(NAME ${_name} COMMAND ${_name})

    ecm_mark_as_test(kmail_grammalecte-${_name})
    target_link_libraries(
        ${_name}
        Qt::Test
        KF6::I18n
        KF6::TextGrammarCheck
    )
endmacro()

add_grammalecte_unittest(grammalecteparsertest.cpp)
add_grammalecte_unittest(grammalecteresultwidgettest.cpp)
add_grammalecte_unittest(grammalectegrammarerrortest.cpp)
if(NOT DISABLE_AUTOTEST_BROKEN_CI)
    add_grammalecte_unittest(grammalecteresultjobtest.cpp)
endif()
add_grammalecte_unittest(grammalecteconfigwidgettest.cpp)
add_grammalecte_unittest(grammalectegenerateconfigoptionjobtest.cpp)
add_grammalecte_unittest(grammalecteconfigdialogtest.cpp)
add_grammalecte_unittest(grammalecteurlrequesterwidgettest.cpp)
