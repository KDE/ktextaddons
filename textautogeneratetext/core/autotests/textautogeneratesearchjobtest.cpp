/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchjobtest.h"
#include "core/jobs/textautogeneratesearchjob.h"
#include <QStandardPaths>
#include <QTest>

using namespace Qt::Literals::StringLiterals;

QTEST_GUILESS_MAIN(TextAutoGenerateSearchJobTest)

TextAutoGenerateSearchJobTest::TextAutoGenerateSearchJobTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void TextAutoGenerateSearchJobTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateSearchJob job(nullptr);
    QVERIFY(job.searchText().isEmpty());
    QVERIFY(!job.canStart());
}

void TextAutoGenerateSearchJobTest::shouldNotStartForWhitespaceOnlySearchText()
{
    TextAutoGenerateText::TextAutoGenerateSearchJob job(nullptr);
    job.setSearchText(u"   \t\n"_s);
    QVERIFY(!job.canStart());
}

#include "moc_textautogeneratesearchjobtest.cpp"
