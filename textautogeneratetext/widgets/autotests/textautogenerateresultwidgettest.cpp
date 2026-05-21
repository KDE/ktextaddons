/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateresultwidgettest.h"
#include "widgets/common/textautogenerateresultwidget.h"
#include <QTest>
QTEST_MAIN(TextAutoGenerateResultWidgetTest)

TextAutoGenerateResultWidgetTest::TextAutoGenerateResultWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateResultWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateResultWidget w(nullptr);
    // TODO
}

#include "moc_textautogenerateresultwidgettest.cpp"
