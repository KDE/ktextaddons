/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratesearchlistviewtest.h"
#include "widgets/view/textautogeneratesearchlistview.h"
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(TextAutoGenerateSearchListViewTest)

TextAutoGenerateSearchListViewTest::TextAutoGenerateSearchListViewTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateSearchListViewTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateSearchListView w(nullptr);
    // TODO
}

#include "moc_textautogeneratesearchlistviewtest.cpp"
