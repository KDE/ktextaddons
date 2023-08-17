# SPDX-FileCopyrightText: none
# SPDX-License-Identifier: BSD-3-Clause
add_executable(slidecontainer_gui slidecontainer_gui.cpp)
target_link_libraries(slidecontainer_gui
    Qt::Core
    Qt::Gui
    Qt::Widgets
    KF${KF_MAJOR_VERSION}::TextAddonsWidgets
    )

