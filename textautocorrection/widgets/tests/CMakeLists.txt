# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
add_executable(autocorrectiontextedit_gui autocorrectiontextedit_gui.cpp)
target_link_libraries(autocorrectiontextedit_gui
  KF${KF_MAJOR_VERSION}::TextAutoCorrectionWidgets
  KF${KF_MAJOR_VERSION}::I18n
)


######
add_executable(autocorrectionwidget_gui autocorrectionwidget_gui.h autocorrectionwidget_gui.cpp)
target_link_libraries(autocorrectionwidget_gui
  KF${KF_MAJOR_VERSION}::TextAutoCorrectionWidgets
  KF${KF_MAJOR_VERSION}::I18n
)
