# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

add_executable(ollamamanagemodelsgui_gui
    ollamamanagemodels_gui.cpp
)

target_link_libraries(ollamamanagemodelsgui_gui
   textautogenerateollama 
)
