# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

macro(add_textaddonswidgets_misc_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h TEST_NAME ${_name}
        LINK_LIBRARIES Qt::Test Qt::Gui KF6::ConfigCore KF6::WidgetsAddons KF6TextAddonsWidgets
    )
endmacro()

add_textaddonswidgets_misc_unittest(loaddialogsizeutilstest.cpp)
