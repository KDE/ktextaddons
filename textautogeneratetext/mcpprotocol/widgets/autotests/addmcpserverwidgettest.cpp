/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "addmcpserverwidgettest.h"
#include "addmcpserverwidget.h"
#include <QLineEdit>
#include <QTest>
QTEST_MAIN(AddMcpServerWidgetTest)
using namespace Qt::Literals::StringLiterals;
AddMcpServerWidgetTest::AddMcpServerWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void AddMcpServerWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolWidgets::AddMcpServerWidget w;
    auto mServerNameLineEdit = w.findChild<QLineEdit *>(u"mServerNameLineEdit"_s);
    QVERIFY(mServerNameLineEdit);
    QVERIFY(mServerNameLineEdit->text().isEmpty());
    QVERIFY(mServerNameLineEdit->isClearButtonEnabled());

    auto mServerUrlLineEdit = w.findChild<QLineEdit *>(u"mServerUrlLineEdit"_s);
    QVERIFY(mServerUrlLineEdit);
    QVERIFY(mServerUrlLineEdit->text().isEmpty());
    QVERIFY(mServerUrlLineEdit->isClearButtonEnabled());
}
#include "moc_addmcpserverwidgettest.cpp"
