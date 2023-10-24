/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskdownloadlanguagejobtest.h"
#include "voskdownloadlanguagejob.h"
#include <QTest>

QTEST_GUILESS_MAIN(VoskDownloadLanguageJobTest)
VoskDownloadLanguageJobTest::VoskDownloadLanguageJobTest(QObject *parent)
    : QObject{parent}
{
}

void VoskDownloadLanguageJobTest::shouldHaveDefaultValues()
{
    VoskDownloadLanguageJob w;
    QVERIFY(!w.canStart());
    QVERIFY(!w.info().isValid());

    VoskDownloadLanguageJob::DownloadLanguageInfo info;
    QVERIFY(info.url.isEmpty());
    QVERIFY(info.checksum.isEmpty());
    QVERIFY(info.name.isEmpty());
}

#include "moc_voskdownloadlanguagejobtest.cpp"
