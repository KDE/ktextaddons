/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "grammalecteresultjobtest.h"
#include "grammalecte/grammalecteresultjob.h"
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(GrammarResultJobTest)
GrammarResultJobTest::GrammarResultJobTest(QObject *parent)
    : QObject(parent)
{
    QStandardPaths::setTestModeEnabled(true);
}

void GrammarResultJobTest::shouldHaveDefaultValue()
{
    TextGrammarCheck::GrammalecteResultJob job;
    QVERIFY(!job.canStart());
    QVERIFY(job.text().isEmpty());
    QVERIFY(job.pythonPath().isEmpty());
    QVERIFY(job.grammarlecteCliPath().isEmpty());
    QVERIFY(job.arguments().isEmpty());
}

void GrammarResultJobTest::shouldBeAbleToStart()
{
    TextGrammarCheck::GrammalecteResultJob job;
    // Args can be empty if we use default values
    QVERIFY(!job.canStart());
    job.setText(QStringLiteral("ff"));
    QVERIFY(!job.canStart());
    job.setPythonPath(QStringLiteral("/usr/bin/"));
    QVERIFY(!job.canStart());
    job.setGrammarlecteCliPath(QStringLiteral("/usr/bin/ls"));
    QVERIFY(job.canStart());
    job.setArguments(QStringList() << QStringLiteral("ff"));
    QVERIFY(job.canStart());
}

#include "moc_grammalecteresultjobtest.cpp"
