/*
   SPDX-FileCopyrightText: 2019-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "languagetoolresultjobtest.h"
using namespace Qt::Literals::StringLiterals;

#include "languagetool/languagetoolresultjob.h"
#include <QTest>
QTEST_MAIN(LanguageToolResultJobTest)
LanguageToolResultJobTest::LanguageToolResultJobTest(QObject *parent)
    : QObject(parent)
{
}

void LanguageToolResultJobTest::shouldHaveDefaultValue()
{
    TextGrammarCheck::LanguageToolResultJob job;
    QVERIFY(!job.networkAccessManager());
    QVERIFY(job.arguments().isEmpty());
    QVERIFY(!job.canStart());
    QVERIFY(job.text().isEmpty());
    QVERIFY(job.url().isEmpty());
    QVERIFY(job.language().isEmpty());
}

void LanguageToolResultJobTest::shouldBeAbleToStart()
{
    TextGrammarCheck::LanguageToolResultJob job;
    QVERIFY(!job.canStart());
    job.setText(u"foo"_s);
    QVERIFY(!job.canStart());
    job.setUrl(u"http://www.kde.org"_s);
    QVERIFY(!job.canStart());
    job.setLanguage(u"foo"_s);
    QVERIFY(!job.canStart());
    QNetworkAccessManager network;
    job.setNetworkAccessManager(&network);
    QVERIFY(job.canStart());
    job.setText(u" "_s);
    QVERIFY(!job.canStart());
    job.setText(u" DDDD"_s);
    QVERIFY(job.canStart());
}

#include "moc_languagetoolresultjobtest.cpp"
