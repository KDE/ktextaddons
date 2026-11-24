/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateagentwidgettest.h"
#include "widgets/promptswidget/textautogenerateagentwidget.h"
#include <KIconButton>
#include <QFormLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QSignalSpy>
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

    auto mIconName = w.findChild<KIconButton *>(u"mIconName"_s);
    QVERIFY(mIconName);
    QVERIFY(mIconName->icon().isEmpty());

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
    agent.setIconName(u"document-edit"_s);
    agent.setDescription(u"description"_s);
    w.setAgent(agent);
    QCOMPARE(w.agent(), agent);

    w.findChild<QLineEdit *>(u"mName"_s)->setText(u"newname"_s);
    const TextAutoGenerateText::TextAutoGenerateAgent result = w.agent();
    QCOMPARE(result.identifier(), "foo"_ba);
    QCOMPARE(result.name(), u"newname"_s);
    QCOMPARE(result.iconName(), u"document-edit"_s);
}

void TextAutoGenerateAgentWidgetTest::shouldEmitEnableOkButton()
{
    TextAutoGenerateText::TextAutoGenerateAgentWidget w;
    QSignalSpy enableOkButtonSpy(&w, &TextAutoGenerateText::TextAutoGenerateAgentWidget::enableOkButton);
    auto mName = w.findChild<QLineEdit *>(u"mName"_s);
    QVERIFY(mName);

    mName->setText(u"foo"_s);
    QCOMPARE(enableOkButtonSpy.count(), 1);
    QVERIFY(enableOkButtonSpy.at(0).at(0).toBool());

    // Whitespace only is not a name.
    mName->setText(u"   "_s);
    QCOMPARE(enableOkButtonSpy.count(), 2);
    QVERIFY(!enableOkButtonSpy.at(1).at(0).toBool());
}

#include "moc_textautogenerateagentwidgettest.cpp"
