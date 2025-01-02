# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>
add_executable(voskdownloadandextractlanguage_gui voskdownloadandextractlanguage_gui.cpp)
target_link_libraries(voskdownloadandextractlanguage_gui
  voskspeechtotext
)

