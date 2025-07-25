/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolgetlistoflanguagejobtest.h"
using namespace Qt::Literals::StringLiterals;

#include "languagetool/languagetoolgetlistoflanguagejob.h"
#include <QTest>
QTEST_GUILESS_MAIN(LanguageToolGetListOfLanguageJobTest)
LanguageToolGetListOfLanguageJobTest::LanguageToolGetListOfLanguageJobTest(QObject *parent)
    : QObject(parent)
{
}

void LanguageToolGetListOfLanguageJobTest::shouldHaveDefaultValues()
{
    TextGrammarCheck::LanguageToolGetListOfLanguageJob w;
    QVERIFY(!w.canStart());
    QVERIFY(w.listOfLanguagePath().isEmpty());
    QVERIFY(w.url().isEmpty());
    QVERIFY(!w.networkAccessManager());
}

void LanguageToolGetListOfLanguageJobTest::shouldBeAbleToStart()
{
    TextGrammarCheck::LanguageToolGetListOfLanguageJob job;
    QVERIFY(!job.canStart());
    job.setUrl(u"foo"_s);
    QVERIFY(!job.canStart());
    QNetworkAccessManager network;
    job.setNetworkAccessManager(&network);
    QVERIFY(job.canStart());
}

#include "moc_languagetoolgetlistoflanguagejobtest.cpp"
