/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratesearchlistviewtest.h"
#include "widgets/view/textautogeneratesearchlistview.h"
#include <QTest>
QTEST_MAIN(TextAutoGenerateSearchListViewTest)

TextAutoGenerateSearchListViewTest::TextAutoGenerateSearchListViewTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateSearchListViewTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateSearchListView w;
    // TODO
}

#include "moc_textautogeneratesearchlistviewtest.cpp"
