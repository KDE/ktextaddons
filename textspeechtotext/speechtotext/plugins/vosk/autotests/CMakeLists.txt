# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>
add_definitions( -DVOSK_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data")

macro(add_voskspeechtotext_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h
        TEST_NAME ${_name}
        NAME_PREFIX "speechtotext-"
        LINK_LIBRARIES Qt::Test
        Qt::Widgets
        libvoskspeechtotext
    )
endmacro()

add_voskspeechtotext_unittest(voskspeechtotextinfotest.cpp)
add_voskspeechtotext_unittest(voskdownloadlanguagejobtest.cpp)
add_voskspeechtotext_unittest(voskextractlanguagejobtest.cpp)
add_voskspeechtotext_unittest(voskenginelanguagewidgettest.cpp)
add_voskspeechtotext_unittest(voskenginedialogtest.cpp)
add_voskspeechtotext_unittest(managermodelvoskspeechtotexttest.cpp)
add_voskspeechtotext_unittest(generateinstalledlanguageinfojobtest.cpp)
add_voskspeechtotext_unittest(voskengineutilstest.cpp)
