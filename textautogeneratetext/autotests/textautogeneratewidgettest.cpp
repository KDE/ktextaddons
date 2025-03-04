/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratewidgettest.h"
#include "widgets/textautogeneratewidget.h"
#include <QTest>
QTEST_MAIN(TextAutogenerateWidgetTest)

TextAutogenerateWidgetTest::TextAutogenerateWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutogenerateWidgetTest::shouldHaveDefaultValues()
{
    TextAutogenerateText::TextAutogenerateWidget w;

    // TODO
}
