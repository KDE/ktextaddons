/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemodelavailablelistviewtest.h"
#include "widgets/availablemodel/textautogeneratemodelavailablelistview.h"
#include <QTest>
QTEST_MAIN(TextAutoGenerateModelAvailableListViewTest)

TextAutoGenerateModelAvailableListViewTest::TextAutoGenerateModelAvailableListViewTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateModelAvailableListViewTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateModelAvailableListView w;
    QCOMPARE(w.verticalScrollMode(), QAbstractItemView::ScrollPerPixel);
    QCOMPARE(w.horizontalScrollBarPolicy(), Qt::ScrollBarAlwaysOff);
    QVERIFY(w.wordWrap());
    QVERIFY(w.hasMouseTracking());
    QCOMPARE(w.focusPolicy(), Qt::NoFocus);
}

#include "moc_textautogeneratemodelavailablelistviewtest.cpp"
