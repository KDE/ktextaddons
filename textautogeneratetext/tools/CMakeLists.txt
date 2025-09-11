# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

# We don't need it in release mode
if(BUILD_TESTING)
    add_subdirectory(example)
endif()
