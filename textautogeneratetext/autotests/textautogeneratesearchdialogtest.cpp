/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchdialogtest.h"
using namespace Qt::Literals::StringLiterals;

#include "widgets/textautogeneratesearchdialog.h"
#include "widgets/textautogeneratesearchwidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutoGenerateSearchDialogTest)

TextAutoGenerateSearchDialogTest::TextAutoGenerateSearchDialogTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateSearchDialogTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateSearchDialog d(nullptr);
    QVERIFY(!d.windowTitle().isEmpty());
    auto mainLayout = d.findChild<QVBoxLayout *>(u"mainLayout"_s);
    QVERIFY(mainLayout);

    auto mTextAutoGenerateSearchWidget = d.findChild<TextAutoGenerateText::TextAutoGenerateSearchWidget *>(u"mTextAutoGenerateSearchWidget"_s);
    QVERIFY(mTextAutoGenerateSearchWidget);

    auto button = d.findChild<QDialogButtonBox *>(u"button"_s);
    QVERIFY(button);
}

#include "moc_textautogeneratesearchdialogtest.cpp"
