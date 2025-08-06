/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextconfigurepromptwidgettext.h"
#include "widgets/textautogeneratetextconfigurepromptwidget.h"
#include <QLabel>
#include <QPlainTextEdit>
#include <QTest>
#include <QVBoxLayout>
using namespace Qt::Literals::StringLiterals;

QTEST_MAIN(TextAutoGenerateTextConfigurePromptWidgetText)
TextAutoGenerateTextConfigurePromptWidgetText::TextAutoGenerateTextConfigurePromptWidgetText(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTextConfigurePromptWidgetText::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTextConfigurePromptWidget w;
    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto label = w.findChild<QLabel *>(u"label"_s);
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());

    auto mSystemPrompt = w.findChild<QPlainTextEdit *>(u"mSystemPrompt"_s);
    QVERIFY(mSystemPrompt);

    QVERIFY(w.systemPrompt().isEmpty());
}

#include "moc_textautogeneratetextconfigurepromptwidgettext.cpp"
