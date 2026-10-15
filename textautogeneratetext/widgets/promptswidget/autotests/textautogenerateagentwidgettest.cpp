/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateagentwidgettest.h"
#include "widgets/promptswidget/textautogenerateagentwidget.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QTest>
QTEST_MAIN(TextAutoGenerateAgentWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateAgentWidgetTest::TextAutoGenerateAgentWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateAgentWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateAgentWidget w;
    auto mainLayout = w.findChild<QFormLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mName = w.findChild<QLineEdit *>(u"mName"_s);
    QVERIFY(mName);
    QVERIFY(mName->text().isEmpty());

    auto mDescription = w.findChild<QPlainTextEdit *>(u"mDescription"_s);
    QVERIFY(mDescription);
    QVERIFY(mDescription->toPlainText().isEmpty());
}

void TextAutoGenerateAgentWidgetTest::shouldKeepIdentifier()
{
    TextAutoGenerateText::TextAutoGenerateAgentWidget w;
    TextAutoGenerateText::TextAutoGenerateAgent agent;
    agent.setIdentifier("foo"_ba);
    agent.setName(u"bla"_s);
    agent.setDescription(u"description"_s);
    w.setAgent(agent);
    QCOMPARE(w.agent(), agent);

    w.findChild<QLineEdit *>(u"mName"_s)->setText(u"newname"_s);
    const TextAutoGenerateText::TextAutoGenerateAgent result = w.agent();
    QCOMPARE(result.identifier(), "foo"_ba);
    QCOMPARE(result.name(), u"newname"_s);
}

#include "moc_textautogenerateagentwidgettest.cpp"
