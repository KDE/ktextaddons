/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratesearchpromptwidgettest.h"
#include "widgets/promptswidget/textautogeneratesearchpromptwidget.h"
#include <QHBoxLayout>
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(TextAutoGenerateSearchPromptWidgetTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateSearchPromptWidgetTest::TextAutoGenerateSearchPromptWidgetTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateSearchPromptWidgetTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateSearchPromptWidget w;
    auto mainLayout = w.findChild<QHBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});
}

#include "moc_textautogeneratesearchpromptwidgettest.cpp"
