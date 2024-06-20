# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

macro(add_speechtotext_widget_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h
        TEST_NAME ${_name}
        NAME_PREFIX "speechtotext-"
        LINK_LIBRARIES Qt::Test
        Qt::Widgets
        KF6::TextSpeechToText
)
endmacro()
add_speechtotext_widget_unittest(speechtotextconfigurewidgettest.cpp)
add_speechtotext_widget_unittest(speechtotextselectdevicewidgettest.cpp)
add_speechtotext_widget_unittest(speechtotextconfiguredialogtest.cpp)
add_speechtotext_widget_unittest(speechtotexttoolbuttonwidgettest.cpp)
