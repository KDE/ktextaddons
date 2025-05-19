# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

macro(add_textautogenerate_core_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h TEST_NAME ${_name}
        NAME_PREFIX "textautogenerate-core-"
        LINK_LIBRARIES Qt::Test KF6::TextAutoGenerateText
)
endmacro()
add_textautogenerate_core_unittest(textautogeneratesearchmessageutilstest.cpp)
