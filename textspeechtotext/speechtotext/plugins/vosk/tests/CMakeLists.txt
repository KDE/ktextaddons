# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
add_executable(voskdownloadandextractlanguage_gui voskdownloadandextractlanguage_gui.cpp)
target_link_libraries(voskdownloadandextractlanguage_gui
  voskspeechtotext
)

