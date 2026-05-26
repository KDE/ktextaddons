# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_executable(whatsnewnggui)
target_sources(
    whatsnewnggui
    PRIVATE
        whatsnewnggui.h
        whatsnewnggui.cpp
)

target_link_libraries(whatsnewnggui KF6::TextAddonsWidgets)
