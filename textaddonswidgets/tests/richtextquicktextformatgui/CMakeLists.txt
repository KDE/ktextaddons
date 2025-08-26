# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_executable(richtextquicktextformatgui)
target_sources(
    richtextquicktextformatgui
    PRIVATE
        richtextquicktextformatgui.cpp
        richtextquicktextformatgui.h
)

target_link_libraries(richtextquicktextformatgui KF6::TextAddonsWidgets)
