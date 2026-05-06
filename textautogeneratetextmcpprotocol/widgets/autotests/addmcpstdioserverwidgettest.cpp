/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpstdioserverwidgettest.h"
#include "server/addmcpstdioserverwidget.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QTest>
QTEST_MAIN(AddMcpStdioServerWidgetTest)
using namespace Qt::Literals::StringLiterals;
AddMcpStdioServerWidgetTest::AddMcpStdioServerWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AddMcpStdioServerWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolWidgets::AddMcpStdioServerWidget w;
    auto mainLayout = w.findChild<QFormLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->spacing(), 0);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mCommandLineEdit = w.findChild<QLineEdit *>(u"mCommandLineEdit"_s);
    QVERIFY(mCommandLineEdit);
    QVERIFY(mCommandLineEdit->text().isEmpty());

    auto mArgumentsLineEdit = w.findChild<QLineEdit *>(u"mArgumentsLineEdit"_s);
    QVERIFY(mArgumentsLineEdit);
    QVERIFY(mArgumentsLineEdit->text().isEmpty());
}
#include "moc_addmcpstdioserverwidgettest.cpp"
