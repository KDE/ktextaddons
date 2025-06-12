/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateaddinstancedialogtest.h"
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
    TextAutoGenerateText::TextAutoGenerateAddInstanceDialog d(nullptr);
    QVERIFY(!d.windowTitle().isEmpty());
    auto mainLayout = d.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    auto mTextAutoGenerateAddInstanceWidget =
        d.findChild<TextAutoGenerateText::TextAutoGenerateAddInstanceWidget *>(QStringLiteral("mTextAutoGenerateAddInstanceWidget"));
    QVERIFY(mTextAutoGenerateAddInstanceWidget);

    auto button = d.findChild<QDialogButtonBox *>(QStringLiteral("button"));
    QVERIFY(button);
    QCOMPARE(button->standardButtons(), QDialogButtonBox::StandardButtons{QDialogButtonBox::Cancel | QDialogButtonBox::Ok});
}

#include "moc_textautogenerateaddinstancedialogtest.cpp"
