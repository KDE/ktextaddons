# SPDX-FileCopyrightText: Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

macro(add_textaddonswidgets_quicksearchbar_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h TEST_NAME ${_name}
            LINK_LIBRARIES Qt::Test Qt::Gui KF6TextAddonsWidgets
    )
endmacro()

add_textaddonswidgets_quicksearchbar_unittest(quicksearchbartest.cpp)
add_textaddonswidgets_quicksearchbar_unittest(quicksearchbarwidgettest.cpp)
