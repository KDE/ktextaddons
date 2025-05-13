/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchdialogtest.h"
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
    TextAutoGenerateText::TextAutoGenerateSearchDialog d;
    auto mainLayout = d.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    auto mTextAutoGenerateSearchWidget = d.findChild<TextAutoGenerateText::TextAutoGenerateSearchWidget *>(QStringLiteral("mTextAutoGenerateSearchWidget"));
    QVERIFY(mTextAutoGenerateSearchWidget);

    auto button = d.findChild<QDialogButtonBox *>(QStringLiteral("button"));
    QVERIFY(button);
}

#include "moc_textautogeneratesearchdialogtest.cpp"
