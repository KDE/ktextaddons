# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
# SPDX-License-Identifier: BSD-3-Clause

macro(add_widgets_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h TEST_NAME ${_name}
        LINK_LIBRARIES Qt::Test KF6::TextCustomEditor Qt::Widgets
        )
endmacro()


add_widgets_unittest(textgotolinewidgettest.cpp)

add_widgets_unittest(textfindwidgettest.cpp)

add_widgets_unittest(textreplacewidgettest.cpp)
