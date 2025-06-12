/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateaddinstancewidgettest.h"
#include "widgets/instancesmanager/textautogenerateaddinstancewidget.h"
#include "widgets/instancesmanager/textautogeneratetextinstancecombobox.h"
#include <QFormLayout>
#include <QLabel>
#include <QLineEdit>
#include <QTest>
QTEST_MAIN(TextAutoGenerateAddInstanceWidgetTest)

TextAutoGenerateAddInstanceWidgetTest::TextAutoGenerateAddInstanceWidgetTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateAddInstanceWidgetTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateAddInstanceWidget w(nullptr);
    auto mainLayout = w.findChild<QFormLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mInstanceComboBox = w.findChild<TextAutoGenerateText::TextAutoGenerateTextInstanceComboBox *>(QStringLiteral("mInstanceComboBox"));
    QVERIFY(mInstanceComboBox);

    auto mNameLineEdit = w.findChild<QLineEdit *>(QStringLiteral("mNameLineEdit"));
    QVERIFY(mNameLineEdit);
    QVERIFY(mNameLineEdit->isClearButtonEnabled());
    QVERIFY(mNameLineEdit->text().isEmpty());
}

#include "moc_textautogenerateaddinstancewidgettest.cpp"
