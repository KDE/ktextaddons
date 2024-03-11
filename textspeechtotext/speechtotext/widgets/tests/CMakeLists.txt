# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
add_executable(speechtotextconfiguredialog_gui speechtotextconfiguredialog_gui.cpp)
target_link_libraries(speechtotextconfiguredialog_gui
	KF6::TextSpeechToText KF6::I18n
)

