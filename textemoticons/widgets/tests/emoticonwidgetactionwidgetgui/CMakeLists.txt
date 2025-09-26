# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_executable(
    emoticonwidgetactionwidgetgui
    emoticonwidgetactionwidgetgui.cpp
    emoticonwidgetactionwidgetgui.h
)

target_link_libraries(
    emoticonwidgetactionwidgetgui
    KF6TextEmoticonsWidgets
    Qt::Gui
    Qt::Widgets
)
