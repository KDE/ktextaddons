/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolconfigdialogtest.h"
#include "languagetool/languagetoolconfigdialog.h"
#include "languagetool/languagetoolconfigwidget.h"
#include <QDialogButtonBox>
#include <QStandardPaths>
#include <QTest>
#include <QVBoxLayout>
QTEST_MAIN(LanguageToolConfigDialogTest)
LanguageToolConfigDialogTest::LanguageToolConfigDialogTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void LanguageToolConfigDialogTest::shouldHaveDefaultValue()
{
    TextGrammarCheck::LanguageToolConfigDialog w(nullptr);
    QVERIFY(!w.windowTitle().isEmpty());

    auto mainLayout = w.findChild<QVBoxLayout *>(QStringLiteral("mainlayout"));
    QVERIFY(mainLayout);

    auto mConfigWidget = w.findChild<TextGrammarCheck::LanguageToolConfigWidget *>(QStringLiteral("configwidget"));
    QVERIFY(mConfigWidget);

    auto box = w.findChild<QDialogButtonBox *>(QStringLiteral("box"));
    QVERIFY(box);
}

#include "moc_languagetoolconfigdialogtest.cpp"
