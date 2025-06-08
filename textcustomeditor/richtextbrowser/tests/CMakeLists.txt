# SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_executable(richtextbrowser_gui richtextbrowser_gui.cpp)
target_link_libraries(
    richtextbrowser_gui
    KF6::TextCustomEditor
    KF6::CoreAddons
    Qt::Widgets
    KF6::I18n
)
