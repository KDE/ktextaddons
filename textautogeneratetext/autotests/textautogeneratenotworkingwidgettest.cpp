/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratenotworkingwidgettest.h"
#include "widgets/common/textautogeneratenotworkingwidget.h"
#include <KMessageWidget>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateNotWorkingWidgetTest)

TextAutoGenerateNotWorkingWidgetTest::TextAutoGenerateNotWorkingWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateNotWorkingWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateNotWorkingWidget w(nullptr);
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mMessageWidget = w.findChild<KMessageWidget *>(QStringLiteral("mMessageWidget"));
    QVERIFY(mMessageWidget);
    QVERIFY(mMessageWidget->text().isEmpty());
}

#include "moc_textautogeneratenotworkingwidgettest.cpp"
