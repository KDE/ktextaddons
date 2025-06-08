# SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_executable(languagetool_gui)
target_sources(
    languagetool_gui
    PRIVATE main.cpp languagetoolwidget.cpp languagetoolwidget.h
)
target_link_libraries(
    languagetool_gui
    KF6::I18n
    KF6::TextGrammarCheck
    Qt::Network
)
