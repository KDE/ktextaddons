/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateaddinstancedialogtest.h"
using namespace Qt::Literals::StringLiterals;

#include "widgets/instancesmanager/textautogenerateaddinstancedialog.h"
#include "widgets/instancesmanager/textautogenerateaddinstancewidget.h"
#include <QDialogButtonBox>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateAddInstanceDialogTest)

TextAutoGenerateAddInstanceDialogTest::TextAutoGenerateAddInstanceDialogTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateAddInstanceDialogTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateAddInstanceDialog d(nullptr);
    QVERIFY(!d.windowTitle().isEmpty());
    auto mainLayout = d.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mTextAutoGenerateAddInstanceWidget = d.findChild<TextAutoGenerateText::TextAutoGenerateAddInstanceWidget *>(u"mTextAutoGenerateAddInstanceWidget"_s);
    QVERIFY(mTextAutoGenerateAddInstanceWidget);

    auto button = d.findChild<QDialogButtonBox *>(u"button"_s);
    QVERIFY(button);
    QCOMPARE(button->standardButtons(), QDialogButtonBox::StandardButtons{QDialogButtonBox::Cancel | QDialogButtonBox::Ok});
}

#include "moc_textautogenerateaddinstancedialogtest.cpp"
