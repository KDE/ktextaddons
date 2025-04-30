# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

add_executable(texttoautogeneratewidget_gui
    texttoautogeneratewidget_gui.cpp
    textautogeneratewidgetgui.h
    textautogeneratewidgetgui.cpp
)

target_link_libraries(texttoautogeneratewidget_gui
    KF6::TextAutogenerateText
)
