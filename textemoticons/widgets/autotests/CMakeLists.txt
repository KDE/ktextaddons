# SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_textemoticonwidgets_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h TEST_NAME ${_name}
        LINK_LIBRARIES Qt::Test KF6::TextEmoticonsWidgets
    )
endmacro()

add_textemoticonwidgets_unittest(emoticontexteditselectortest.cpp)
add_textemoticonwidgets_unittest(emojilistviewtest.cpp)
add_textemoticonwidgets_unittest(emoticoncategorybuttonstest.cpp)
add_textemoticonwidgets_unittest(emojicategorybuttontest.cpp)
add_textemoticonwidgets_unittest(emoticontonecomboboxtest.cpp)
add_textemoticonwidgets_unittest(emoticonwidgetactiontest.cpp)
add_textemoticonwidgets_unittest(emoticonwidgetactionwidgettest.cpp)
