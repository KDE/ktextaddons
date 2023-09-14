# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>
add_executable(speechtotextconfiguredialog_gui speechtotextconfiguredialog_gui.cpp)
target_link_libraries(speechtotextconfiguredialog_gui
	KF${KF_MAJOR_VERSION}::TextSpeechToText KF${KF_MAJOR_VERSION}::I18n
)

