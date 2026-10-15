/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateselectskillwidgettest.h"
#include "core/models/textautogeneratetextskillmodel.h"
#include "widgets/promptswidget/textautogenerateselectskilllistwidget.h"
#include "widgets/promptswidget/textautogenerateselectskillwidget.h"
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateSelectSkillWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateSelectSkillWidgetTest::TextAutoGenerateSelectSkillWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateSelectSkillWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateSelectSkillWidget w(nullptr);
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mListWidget = w.findChild<TextAutoGenerateText::TextAutoGenerateSelectSkillListWidget *>(u"mListWidget"_s);
    QVERIFY(mListWidget);

    auto mSkillModel = w.findChild<TextAutoGenerateText::TextAutoGenerateTextSkillModel *>(u"mSkillModel"_s);
    QVERIFY(mSkillModel);
    QCOMPARE(mListWidget->model(), mSkillModel);
    QVERIFY(w.skills().isEmpty());
}

#include "moc_textautogenerateselectskillwidgettest.cpp"
