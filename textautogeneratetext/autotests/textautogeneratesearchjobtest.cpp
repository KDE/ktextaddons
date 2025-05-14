/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchjobtest.h"
#include "core/textautogeneratesearchjob.h"
#include <QTest>
QTEST_GUILESS_MAIN(TextAutoGenerateSearchJobTest)

TextAutoGenerateSearchJobTest::TextAutoGenerateSearchJobTest(QObject *parent)
    : QObject{parent}
{
}

void TextAutoGenerateSearchJobTest::shouldHaveDefaultValues()
{
    TextAutoGenerateText::TextAutoGenerateSearchJob job;
    QVERIFY(job.searchText().isEmpty());
    QVERIFY(!job.canStart());
}

#include "moc_textautogeneratesearchjobtest.cpp"
