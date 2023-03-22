# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: none
add_executable(translator_gui translator_gui.cpp)
target_link_libraries(translator_gui
  KF${KF_MAJOR_VERSION}::TextTranslator KF${KF_MAJOR_VERSION}::I18n
)

######
add_executable(translatorconfigurelanguagelistwidget_gui translatorconfigurelanguagelistwidget_gui.cpp translatorconfigurelanguagelistwidget_gui.h)
target_link_libraries(translatorconfigurelanguagelistwidget_gui
  KF${KF_MAJOR_VERSION}::TextTranslator KF${KF_MAJOR_VERSION}::I18n
)
