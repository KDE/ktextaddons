# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_textemoticonwidgets_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h TEST_NAME ${_name}
        LINK_LIBRARIES Qt::Test KF6::TextEmoticonsWidgets Qt::Widgets
)
endmacro()

add_textemoticonwidgets_unittest( emoticontexteditselectortest.cpp)
add_textemoticonwidgets_unittest(emoticonlistviewtest.cpp)
add_textemoticonwidgets_unittest(emoticoncategorybuttonstest.cpp)
add_textemoticonwidgets_unittest(emoticoncategorybuttontest.cpp)
