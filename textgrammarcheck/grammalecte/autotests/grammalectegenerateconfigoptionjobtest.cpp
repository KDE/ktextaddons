/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalectegenerateconfigoptionjobtest.h"
using namespace Qt::Literals::StringLiterals;

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
    job.setPythonPath(u"ff"_s);
    QVERIFY(!job.canStart());
    job.setGrammarlecteCliPath(u"ff"_s);
    QVERIFY(job.canStart());
}

#include "moc_grammalectegenerateconfigoptionjobtest.cpp"
