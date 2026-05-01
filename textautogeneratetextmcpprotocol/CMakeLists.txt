# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
add_definitions(-DTRANSLATION_DOMAIN=\"libtextautogeneratetextmcpprotocol\")
add_subdirectory(core)
if(BUILD_TESTING)
    add_subdirectory(tests)
endif()
add_subdirectory(widgets)
add_subdirectory(plugins)
