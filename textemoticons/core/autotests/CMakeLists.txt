# SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_textemoticon_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h TEST_NAME ${_name}
        LINK_LIBRARIES Qt::Test KF6::TextEmoticonsCore
    )
endmacro()

add_textemoticon_unittest( emoticoncategorytest.cpp)
add_textemoticon_unittest( emoticonunicodeutilstest.cpp)
add_textemoticon_unittest( emojisortfilterproxymodeltest.cpp)
add_textemoticon_unittest( unicodeemoticontest.cpp)
add_textemoticon_unittest( emojimodeltest.cpp)
add_textemoticon_unittest( customemojitest.cpp)
add_textemoticon_unittest( customemojiiconmanagertest.cpp)
add_textemoticon_unittest( unicodeemoticonmanagertest.cpp)
