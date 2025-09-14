/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetoolswidgettest.h"
#include "widgets/toolswidget/textautogeneratetoolswidget.h"
#include <QTest>
QTEST_MAIN(TextAutoGenerateToolsWidgetTest)

TextAutoGenerateToolsWidgetTest::TextAutoGenerateToolsWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateToolsWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateToolsWidget w;
    QVERIFY(w.generateListOfActiveTools().isEmpty());
    // TODO
}

#include "moc_textautogeneratetoolswidgettest.cpp"
