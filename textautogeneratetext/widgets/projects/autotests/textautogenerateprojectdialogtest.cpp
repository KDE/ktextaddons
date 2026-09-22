/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateprojectdialogtest.h"
#include "widgets/projects/textautogenerateprojectdialog.h"
#include "widgets/projects/textautogenerateprojectwidget.h"
#include <QDialogButtonBox>
#include <QLineEdit>
#include <QPushButton>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateProjectDialogTest)
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateProjectDialogTest::TextAutoGenerateProjectDialogTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateProjectDialogTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateText::TextAutoGenerateProjectDialog d;
    QVERIFY(!d.windowTitle().isEmpty());

    auto mainLayout = d.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mProjectWidget = d.findChild<TextAutoGenerateText::TextAutoGenerateProjectWidget *>(u"mProjectWidget"_s);
    QVERIFY(mProjectWidget);

    auto button = d.findChild<QDialogButtonBox *>(u"button"_s);
    QVERIFY(button);

    auto mOkButton = d.findChild<QPushButton *>(u"mOkButton"_s);
    QVERIFY(mOkButton);
    QVERIFY(!mOkButton->isEnabled());
}

void TextAutoGenerateProjectDialogTest::shouldEnableOkButtonWhenNameIsNotEmpty()
{
    TextAutoGenerateText::TextAutoGenerateProjectDialog d;
    auto mOkButton = d.findChild<QPushButton *>(u"mOkButton"_s);
    QVERIFY(mOkButton);
    auto mName = d.findChild<QLineEdit *>(u"mName"_s);
    QVERIFY(mName);

    mName->setText(u"foo"_s);
    QVERIFY(mOkButton->isEnabled());
    QCOMPARE(d.project().name(), u"foo"_s);

    mName->clear();
    QVERIFY(!mOkButton->isEnabled());
}
#include "moc_textautogenerateprojectdialogtest.cpp"
