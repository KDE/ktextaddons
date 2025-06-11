/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateaddinstancewidgettest.h"
#include "widgets/textautogenerateaddinstancewidget.h"
#include "widgets/textautogeneratetextinstancecombobox.h"
#include <QLabel>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateAddInstanceWidgetTest)

TextAutoGenerateAddInstanceWidgetTest::TextAutoGenerateAddInstanceWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateAddInstanceWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateAddInstanceWidget w(nullptr);
    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto label = w.findChild<QLabel *>(QStringLiteral("label"));
    QVERIFY(label);
    QVERIFY(!label->text().isEmpty());

    auto mInstanceComboBox = w.findChild<TextAutoGenerateText::TextAutoGenerateTextInstanceComboBox *>(QStringLiteral("mInstanceComboBox"));
    QVERIFY(mInstanceComboBox);
}
