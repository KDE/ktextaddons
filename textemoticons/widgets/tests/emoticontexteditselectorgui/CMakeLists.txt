# SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_executable(emoticontexteditselector_gui emoticontexteditselector_gui.cpp)

target_link_libraries(
    emoticontexteditselector_gui
    KF6TextEmoticonsWidgets
    Qt::Gui
    Qt::Widgets
)
