# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
include_directories(${CMAKE_CURRENT_BINARY_DIR}/)

if(BUILD_TESTING)
    add_subdirectory(autotests)
endif()
