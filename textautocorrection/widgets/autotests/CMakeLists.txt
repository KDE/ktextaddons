# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
macro(add_autocorrectwidgets_unittest _source)
  set(_test ${_source})
  get_filename_component(_name ${_source} NAME_WE)
  add_executable( ${_name} ${_test} ${_name}.h)
  add_test(NAME ${_name} COMMAND ${_name} )
  set_tests_properties(${_name} PROPERTIES ENVIRONMENT "QT_HASH_SEED=0")
  ecm_mark_as_test(autocorrectionwidgets-${_name})
  target_link_libraries(${_name}  Qt::Test KF${KF_MAJOR_VERSION}::TextAutoCorrectionWidgets)
endmacro()

add_autocorrectwidgets_unittest(autocorrectiontextedittest.cpp)
