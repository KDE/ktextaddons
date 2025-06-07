# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

add_executable(texttoautogeneratequickask_gui
    texttoautogeneratequickask_gui.cpp
)

target_link_libraries(texttoautogeneratequickask_gui
    KF6::TextAutoGenerateText
)

