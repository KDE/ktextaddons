/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratedialogtest.h"
#include "widgets/textautogeneratedialog.h"
#include "widgets/textautogeneratewidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutogenerateDialogTest)

TextAutogenerateDialogTest::TextAutogenerateDialogTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutogenerateDialogTest::shouldHaveDefaultValues()
{
    TextAutogenerateText::TextAutogenerateDialog d;
    auto mainLayout = d.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    auto mTextAutogenerateWidget = d.findChild<TextAutogenerateText::TextAutogenerateWidget *>(QStringLiteral("mTextAutogenerateWidget"));
    QVERIFY(mTextAutogenerateWidget);

    auto button = d.findChild<QDialogButtonBox *>(QStringLiteral("button"));
    QVERIFY(button);
}

#include "moc_textautogeneratedialogtest.cpp"
