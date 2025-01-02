# SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>
# SPDX-License-Identifier: BSD-3-Clause

add_executable(grammalecte_gui)
target_sources(grammalecte_gui PRIVATE main.cpp grammalectewidget.cpp grammalectewidget.h)
target_link_libraries(grammalecte_gui
    KF6::I18n KF6::TextGrammarCheck
)

