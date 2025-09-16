/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetoolswidgettest.h"
#include "widgets/common/textautogenerateflowlayout.h"
#include "widgets/toolswidget/textautogeneratetoolswidget.h"
#include <QLabel>
#include <QTest>
QTEST_MAIN(TextAutoGenerateToolsWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateToolsWidgetTest::TextAutoGenerateToolsWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateToolsWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateToolsWidget w;
    QVERIFY(w.generateListOfActiveTools().isEmpty());

    auto mainLayout = w.findChild<TextAutoGenerateText::TextAutoGenerateFlowLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto label = w.findChild<QLabel *>(u"label"_s);
    QVERIFY(label);
    QVERIFY(label->font().bold());
}

#include "moc_textautogeneratetoolswidgettest.cpp"
