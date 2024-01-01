/*
   SPDX-FileCopyrightText: 2019-2024 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalectegenerateconfigoptionjobtest.h"
#include "grammalecte/grammalectegenerateconfigoptionjob.h"
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(GrammalecteGenerateConfigOptionJobTest)

GrammalecteGenerateConfigOptionJobTest::GrammalecteGenerateConfigOptionJobTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void GrammalecteGenerateConfigOptionJobTest::shouldHaveDefaultValue()
{
    TextGrammarCheck::GrammalecteGenerateConfigOptionJob job;
    QVERIFY(!job.canStart());

    TextGrammarCheck::GrammalecteGenerateConfigOptionJob::Option opt;
    QVERIFY(opt.optionName.isEmpty());
    QVERIFY(opt.description.isEmpty());
    QVERIFY(!opt.defaultValue);
}

void GrammalecteGenerateConfigOptionJobTest::shouldBeAbleToStart()
{
    TextGrammarCheck::GrammalecteGenerateConfigOptionJob job;
    QVERIFY(!job.canStart());
    job.setPythonPath(QStringLiteral("ff"));
    QVERIFY(!job.canStart());
    job.setGrammarlecteCliPath(QStringLiteral("ff"));
    QVERIFY(job.canStart());
}

#include "moc_grammalectegenerateconfigoptionjobtest.cpp"
