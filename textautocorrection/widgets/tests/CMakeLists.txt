# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>
add_executable(autocorrectiontextedit_gui autocorrectiontextedit_gui.cpp)
target_link_libraries(
    autocorrectiontextedit_gui
    KF6::TextAutoCorrectionWidgets
    KF6::I18n
)

######
add_executable(
    autocorrectionwidget_gui
    autocorrectionwidget_gui.h
    autocorrectionwidget_gui.cpp
)
target_link_libraries(
    autocorrectionwidget_gui
    KF6::TextAutoCorrectionWidgets
    KF6::I18n
    KF6::ConfigCore
)
