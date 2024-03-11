# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
# SPDX-License-Identifier: BSD-3-Clause
macro(add_textedit_texttospeech_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h TEST_NAME ${_name}
        NAME_PREFIX "texttospeech-"
        LINK_LIBRARIES Qt::Test KF6::TextEditTextToSpeech Qt::Widgets Qt::TextToSpeech
        )
endmacro()

add_textedit_texttospeech_unittest( texttospeechwidgettest.cpp )
add_textedit_texttospeech_unittest( texttospeechconfigwidgettest.cpp )
add_textedit_texttospeech_unittest( texttospeechactionstest.cpp )
add_textedit_texttospeech_unittest( texttospeechsliderwidgettest.cpp )
add_textedit_texttospeech_unittest( texttospeechutiltest.cpp )
