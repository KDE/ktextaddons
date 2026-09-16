# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

macro(add_whisperinstallspeechtotext_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h
        TEST_NAME ${_name}
        NAME_PREFIX "speechtotext-"
        LINK_LIBRARIES Qt::Test
        Qt::Widgets
        speechtotextwhisperinstall
    )
endmacro()

add_whisperinstallspeechtotext_unittest(whisperspeechtotextutilstest.cpp)
add_whisperinstallspeechtotext_unittest(whisperspeechtotextcheckjobtest.cpp)
add_whisperinstallspeechtotext_unittest(whisperspeechtotextmodelsjobtest.cpp)
add_whisperinstallspeechtotext_unittest(whisperspeechtotextdownloadmodeljobtest.cpp)
add_whisperinstallspeechtotext_unittest(whisperspeechtotextcachedmodelsjobtest.cpp)
add_whisperinstallspeechtotext_unittest(whisperspeechtotextmodelcomboboxtest.cpp)
add_whisperinstallspeechtotext_unittest(whisperspeechtotextinstalljobtest.cpp)
add_whisperinstallspeechtotext_unittest(whisperspeechtotextinstallpythonevenvjobtest.cpp)
add_whisperinstallspeechtotext_unittest(whisperspeechtotextinstallpythonwidgettest.cpp)
add_whisperinstallspeechtotext_unittest(whisperspeechtotextinstallpythondialogtest.cpp)
add_whisperinstallspeechtotext_unittest(whisperspeechtotextinstallmessagewidgettest.cpp)
