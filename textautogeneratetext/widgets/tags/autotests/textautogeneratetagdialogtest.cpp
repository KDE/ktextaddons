/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetagdialogtest.h"
#include "widgets/tags/textautogeneratetagdialog.h"
#include "widgets/tags/textautogeneratetagwidget.h"
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateTagDialogTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTagDialogTest::TextAutoGenerateTagDialogTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateTagDialogTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateTagDialog d;
    QVERIFY(!d.windowTitle().isEmpty());

    auto mainLayout = d.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mTagWidget = d.findChild<TextAutoGenerateText::TextAutoGenerateTagWidget *>(u"mTagWidget"_s);
    QVERIFY(mTagWidget);

    auto button = d.findChild<QDialogButtonBox *>(u"button"_s);
    QVERIFY(button);

    auto mOkButton = d.findChild<QPushButton *>(u"mOkButton"_s);
    QVERIFY(mOkButton);
    QVERIFY(!mOkButton->isEnabled());
}

void TextAutoGenerateTagDialogTest::shouldEnableOkButtonWhenNameIsNotEmpty()
{
    TextAutoGenerateText::TextAutoGenerateTagDialog d;
    auto mOkButton = d.findChild<QPushButton *>(u"mOkButton"_s);
    QVERIFY(mOkButton);
    auto mName = d.findChild<QLineEdit *>(u"mName"_s);
    QVERIFY(mName);

    mName->setText(u"foo"_s);
    QVERIFY(mOkButton->isEnabled());
    QCOMPARE(d.tag().name(), u"foo"_s);

    mName->clear();
    QVERIFY(!mOkButton->isEnabled());
}
#include "moc_textautogeneratetagdialogtest.cpp"
