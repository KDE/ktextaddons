/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateaddmcpserverwidgettest.h"
#include "widgets/mcpserver/textautogenerateaddmcpserverwidget.h"
#include <QLineEdit>
#include <QTest>
QTEST_MAIN(TextAutoGenerateAddMcpServerWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateAddMcpServerWidgetTest::TextAutoGenerateAddMcpServerWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateAddMcpServerWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateAddMcpServerWidget w;
    auto mServerNameLineEdit = w.findChild<QLineEdit *>(u"mServerNameLineEdit"_s);
    QVERIFY(mServerNameLineEdit);
    QVERIFY(mServerNameLineEdit->text().isEmpty());
    QVERIFY(mServerNameLineEdit->isClearButtonEnabled());

    auto mServerUrlLineEdit = w.findChild<QLineEdit *>(u"mServerUrlLineEdit"_s);
    QVERIFY(mServerUrlLineEdit);
    QVERIFY(mServerUrlLineEdit->text().isEmpty());
    QVERIFY(mServerUrlLineEdit->isClearButtonEnabled());
}
#include "moc_textautogenerateaddmcpserverwidgettest.cpp"
