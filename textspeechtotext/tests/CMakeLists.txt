# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2024-2026 Laurent Montel <montel@kde.org>
add_executable(speechtotextconfigdialog_gui speechtotextconfigdialog_gui.cpp)
target_link_libraries(
    speechtotextconfigdialog_gui
    KF6::TextSpeechToText
    KF6::I18n
)

####

add_executable(speechtotextgui speechtotextgui.cpp)
target_link_libraries(
    speechtotextgui
    KF6::TextSpeechToText
    KF6::I18n
)
