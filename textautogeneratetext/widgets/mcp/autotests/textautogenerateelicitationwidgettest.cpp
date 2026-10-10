/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateelicitationwidgettest.h"
#include "widgets/mcp/textautogenerateelicitationwidget.h"
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateElicitationWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateElicitationWidgetTest::TextAutoGenerateElicitationWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateElicitationWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateElicitationWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});
}
#include "moc_textautogenerateelicitationwidgettest.cpp"
