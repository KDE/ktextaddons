/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateconfiguredialogtest.h"
#include "widgets/textautogenerateconfiguredialog.h"
#include "widgets/textautogenerateconfigurewidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(TextAutogenerateConfigureDialogTest)

TextAutogenerateConfigureDialogTest::TextAutogenerateConfigureDialogTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutogenerateConfigureDialogTest::shouldHaveDefaultValues()
{
    TextAutogenerateText::TextAutogenerateConfigureDialog d;
    auto mainLayout = d.findChild<QVBoxLayout *>(QStringLiteral("mainLayout"));
    QVERIFY(mainLayout);

    auto mTextAutogenerateConfigureWidget =
        d.findChild<TextAutogenerateText::TextAutogenerateConfigureWidget *>(QStringLiteral("mTextAutogenerateConfigureWidget"));
    QVERIFY(mTextAutogenerateConfigureWidget);

    auto button = d.findChild<QDialogButtonBox *>(QStringLiteral("button"));
    QVERIFY(button);
}

#include "moc_textautogenerateconfiguredialogtest.cpp"
