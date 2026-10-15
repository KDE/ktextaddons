/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateskillwidgettest.h"
#include "widgets/promptswidget/textautogenerateskillwidget.h"
#include <QFormLayout>
#include <QLineEdit>
#include <QPlainTextEdit>
#include <QTest>
QTEST_MAIN(TextAutoGenerateSkillWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateSkillWidgetTest::TextAutoGenerateSkillWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateSkillWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateSkillWidget w;
    auto mainLayout = w.findChild<QFormLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mName = w.findChild<QLineEdit *>(u"mName"_s);
    QVERIFY(mName);
    QVERIFY(mName->text().isEmpty());

    auto mDescription = w.findChild<QLineEdit *>(u"mDescription"_s);
    QVERIFY(mDescription);
    QVERIFY(mDescription->text().isEmpty());

    auto mInstructions = w.findChild<QPlainTextEdit *>(u"mInstructions"_s);
    QVERIFY(mInstructions);
    QVERIFY(mInstructions->toPlainText().isEmpty());
}

void TextAutoGenerateSkillWidgetTest::shouldKeepIdentifier()
{
    TextAutoGenerateText::TextAutoGenerateSkillWidget w;
    TextAutoGenerateText::TextAutoGenerateSkill skill;
    skill.setIdentifier("foo"_ba);
    skill.setName(u"bla"_s);
    skill.setDescription(u"description"_s);
    skill.setInstructions(u"instructions"_s);
    w.setSkill(skill);
    QCOMPARE(w.skill(), skill);

    w.findChild<QLineEdit *>(u"mName"_s)->setText(u"newname"_s);
    const TextAutoGenerateText::TextAutoGenerateSkill result = w.skill();
    QCOMPARE(result.identifier(), "foo"_ba);
    QCOMPARE(result.name(), u"newname"_s);
}

#include "moc_textautogenerateskillwidgettest.cpp"
