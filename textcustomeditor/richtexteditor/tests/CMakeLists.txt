# SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_executable(richtexteditor_gui richtexteditor_gui.cpp)
target_link_libraries(
    richtexteditor_gui
    KF6::TextCustomEditor
    KF6::CoreAddons
    Qt::Widgets
    KF6::I18n
)
