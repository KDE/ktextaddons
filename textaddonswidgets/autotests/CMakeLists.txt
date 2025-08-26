# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause

macro(add_textaddonswidgets_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h TEST_NAME ${_name}
	    LINK_LIBRARIES Qt::Test Qt::Gui KF6TextAddonsWidgets
    )
endmacro()

add_textaddonswidgets_unittest(slidecontainertest.cpp)
