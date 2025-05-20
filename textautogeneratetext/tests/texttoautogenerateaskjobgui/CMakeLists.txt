# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

add_executable(texttoautogenerateaskjob_gui
    texttoautogenerateaskjob_gui.cpp
    textautogenerateaskjobwidget.h
    textautogenerateaskjobwidget.cpp
)

target_link_libraries(texttoautogenerateaskjob_gui
    KF6::TextAutoGenerateText
)
