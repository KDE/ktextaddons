/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateaddinstancewidgettest.h"
using namespace Qt::Literals::StringLiterals;

#include "widgets/instancesmanager/textautogenerateaddinstancewidget.h"
#include "widgets/instancesmanager/textautogeneratetextinstancecombobox.h"
#include <QFormLayout>
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
    auto mainLayout = w.findChild<QFormLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);
    QCOMPARE(mainLayout->contentsMargins(), QMargins{});

    auto mInstanceComboBox = w.findChild<TextAutoGenerateText::TextAutoGenerateTextInstanceComboBox *>(u"mInstanceComboBox"_s);
    QVERIFY(mInstanceComboBox);

    auto mNameLineEdit = w.findChild<QLineEdit *>(u"mNameLineEdit"_s);
    QVERIFY(mNameLineEdit);
    QVERIFY(mNameLineEdit->isClearButtonEnabled());
    QVERIFY(mNameLineEdit->text().isEmpty());
}

#include "moc_textautogenerateaddinstancewidgettest.cpp"
