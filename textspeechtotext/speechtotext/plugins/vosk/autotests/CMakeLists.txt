# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

macro(add_voskspeechtotext_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h
        TEST_NAME ${_name}
        NAME_PREFIX "speechtotext-"
        LINK_LIBRARIES Qt::Test
        Qt::Core
        libvoskspeechtotext
    )
endmacro()

add_voskspeechtotext_unittest(voskspeechtotextinfotest.cpp)
