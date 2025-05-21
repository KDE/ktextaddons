# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

add_executable(texttoautogeneratetypingindicatorgui_gui
    texttoautogeneratetypingindicatorgui_gui.cpp
    texttoautogeneratetypingindicatorgui.cpp
    texttoautogeneratetypingindicatorgui.h
)

target_link_libraries(texttoautogeneratetypingindicatorgui_gui
    KF6::TextAutoGenerateText
)
