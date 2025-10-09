/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratequicksearchbartest.h"
#include "widgets/view/textautogeneratequicksearchbar.h"
#include <QTest>
QTEST_MAIN(TextAutoGenerateQuickSearchBarTest)

TextAutoGenerateQuickSearchBarTest::TextAutoGenerateQuickSearchBarTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateQuickSearchBarTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateQuickSearchBar w;
    // TODO
}

#include "moc_textautogeneratequicksearchbartest.cpp"
