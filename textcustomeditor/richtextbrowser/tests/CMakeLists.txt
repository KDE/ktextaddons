# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
# SPDX-License-Identifier: BSD-3-Clause
add_executable(richtextbrowser_gui richtextbrowser_gui.cpp)
target_link_libraries(richtextbrowser_gui
  KF${KF_MAJOR_VERSION}::TextCustomEditor KF${KF_MAJOR_VERSION}::CoreAddons Qt::Widgets KF${KF_MAJOR_VERSION}::I18n
)

