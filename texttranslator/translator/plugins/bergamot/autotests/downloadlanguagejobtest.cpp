/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "downloadlanguagejobtest.h"
#include "downloadlanguagejob.h"
#include <QTest>

QTEST_GUILESS_MAIN(DownloadLanguageJobTest)
DownloadLanguageJobTest::DownloadLanguageJobTest(QObject *parent)
    : QObject{parent}
{
}

void DownloadLanguageJobTest::shouldHaveDefaultValues()
{
    DownloadLanguageJob w;
    QVERIFY(!w.canStart());
    QVERIFY(w.url().isEmpty());
    QVERIFY(w.checkSum().isEmpty());
}

#include "moc_downloadlanguagejobtest.cpp"
