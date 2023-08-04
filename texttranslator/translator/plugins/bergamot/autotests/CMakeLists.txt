# SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

macro(add_translator_bergamot_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h
        TEST_NAME ${_name}
        NAME_PREFIX "translator-"
        LINK_LIBRARIES Qt::Test
        Qt::Widgets
        libbergamot
    )
endmacro()
add_translator_bergamot_unittest(bergamotengineutilstest.cpp)
add_translator_bergamot_unittest(translatortest.cpp)
add_translator_bergamot_unittest(bergamotenginewidgettest.cpp)
add_translator_bergamot_unittest(bergamotenginelanguagewidgettest.cpp)
