# SPDX-License-Identifier: BSD-3-Clause
# SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>
add_executable(translator_gui translator_gui.cpp)
target_link_libraries(translator_gui
  KF6::TextTranslator KF6::I18n
)

######
add_executable(translatorconfigurelanguagelistwidget_gui translatorconfigurelanguagelistwidget_gui.cpp translatorconfigurelanguagelistwidget_gui.h)
target_link_libraries(translatorconfigurelanguagelistwidget_gui
  KF6::TextTranslator KF6::I18n
)

#####
add_executable(translatorconfigurelistswidget_gui translatorconfigurelistswidget_gui.cpp)
target_link_libraries(translatorconfigurelistswidget_gui
  KF6::TextTranslator KF6::I18n
)
