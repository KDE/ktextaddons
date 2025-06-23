/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolconfigdialogtest.h"
using namespace Qt::Literals::StringLiterals;

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

    auto mainLayout = w.findChild<QVBoxLayout *>(u"mainlayout"_s);
    QVERIFY(mainLayout);

    auto mConfigWidget = w.findChild<TextGrammarCheck::LanguageToolConfigWidget *>(u"configwidget"_s);
    QVERIFY(mConfigWidget);

    auto box = w.findChild<QDialogButtonBox *>(u"box"_s);
    QVERIFY(box);
}

#include "moc_languagetoolconfigdialogtest.cpp"
