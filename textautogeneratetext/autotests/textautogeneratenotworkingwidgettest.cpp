/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratenotworkingwidgettest.h"
#include "widgets/textautogeneratenotworkingwidget.h"
#include <QTest>
QTEST_MAIN(TextAutogenerateNotWorkingWidgetTest)

TextAutogenerateNotWorkingWidgetTest::TextAutogenerateNotWorkingWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutogenerateNotWorkingWidgetTest::shouldHaveDefaultValues()
{
    TextAutogenerateText::TextAutogenerateNotWorkingWidget w;
    // TODO
}

#include "moc_textautogeneratenotworkingwidgettest.cpp"
