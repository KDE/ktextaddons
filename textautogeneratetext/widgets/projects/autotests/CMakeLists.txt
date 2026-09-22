# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

macro(add_textautogenerate_widgets_projects_unittest _source)
    get_filename_component(_name ${_source} NAME_WE)
    ecm_add_test(${_source} ${_name}.h TEST_NAME ${_name}
        NAME_PREFIX "textautogenerate-widget-projects-"
        LINK_LIBRARIES Qt::Test KF6::TextAutoGenerateText KF6::WidgetsAddons
    )
endmacro()

add_textautogenerate_widgets_projects_unittest(textautogenerateprojectwidgettest.cpp)
add_textautogenerate_widgets_projects_unittest(textautogenerateprojectdialogtest.cpp)
add_textautogenerate_widgets_projects_unittest(textautogeneratemanageprojectswidgettest.cpp)
add_textautogenerate_widgets_projects_unittest(textautogeneratemanageprojectsdialogtest.cpp)
add_textautogenerate_widgets_projects_unittest(textautogenerateprojectsmenutest.cpp)
