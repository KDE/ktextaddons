# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

macro(add_textautogenerate_core_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h TEST_NAME ${_name}
        NAME_PREFIX "textautogenerate-core-"
        LINK_LIBRARIES Qt::Test KF6::TextAutoGenerateText Qt::Sql
    )
endmacro()
add_textautogenerate_core_unittest(textautogeneratesearchmessageutilstest.cpp)
add_textautogenerate_core_unittest(textautogenerateexportchatbasejobtest.cpp)
add_textautogenerate_core_unittest(textautogeneratemessagetest.cpp)
add_textautogenerate_core_unittest(textautogeneratemanagertest.cpp)
add_textautogenerate_core_unittest(textautogeneratechattest.cpp)
add_textautogenerate_core_unittest(textautogeneratetextplugintest.cpp)
add_textautogenerate_core_unittest(textautogeneratetextinstancetest.cpp)
add_textautogenerate_core_unittest(textautogeneratesearchmessagetest.cpp)
add_textautogenerate_core_unittest(textautogenerateaskjobtest.cpp)
add_textautogenerate_core_unittest(textautogeneratetextinstancesmanagertest.cpp)
add_textautogenerate_core_unittest(textautogeneratesearchjobtest.cpp)
add_textautogenerate_core_unittest(textautogeneratechatsettingstest.cpp)
add_textautogenerate_core_unittest(textautogeneratelocaldatabaseutilstest.cpp)
add_textautogenerate_core_unittest(textautogeneratelocaldatabaseabstracttest.cpp)
add_textautogenerate_core_unittest(textautogeneratelocalchatsdatabasetest.cpp)
add_textautogenerate_core_unittest(textautogeneratelocalmessagesdatabasetest.cpp)
