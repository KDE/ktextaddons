# SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DBERGAMOT_DATA_DIR="${CMAKE_CURRENT_SOURCE_DIR}/data")

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
add_translator_bergamot_unittest(begamotenginedialogtest.cpp)
add_translator_bergamot_unittest(bergamotenginesettingswidgettest.cpp)
add_translator_bergamot_unittest(managermodeltranslatortest.cpp)
add_translator_bergamot_unittest(extractlanguagejobtest.cpp)
add_translator_bergamot_unittest(downloadlanguagejobtest.cpp)
