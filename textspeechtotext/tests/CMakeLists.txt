# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2024 Laurent Montel <montel.org>
add_executable(speechtotext_gui speechtotext_gui.cpp)
target_link_libraries(speechtotext_gui
	KF6::TextSpeechToText KF6::I18n
)

