# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_texttospeech_kokoroinstall_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h TEST_NAME ${_name}
        NAME_PREFIX "texttospeech-kokoroinstall-"
        LINK_LIBRARIES Qt::Test kokoroinstalltexttospeech
    )
endmacro()

add_texttospeech_kokoroinstall_unittest(texttospeechkokoroutilstest.cpp)
add_texttospeech_kokoroinstall_unittest(texttospeechkokoroinstallpythondialogtest.cpp)
add_texttospeech_kokoroinstall_unittest(texttospeechkokoroinstallpythonwidgettest.cpp)
add_texttospeech_kokoroinstall_unittest(texttospeechkokorovoicecomboboxtest.cpp)
