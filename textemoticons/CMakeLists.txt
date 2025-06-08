# SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause
add_definitions(-DTRANSLATION_DOMAIN=\"libtextemoticons\")

add_subdirectory(core)
add_subdirectory(widgets)
if(BUILD_QUICK)
    add_subdirectory(quick)
endif()
