/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "extractlanguagejobtest.h"
#include "extractlanguagejob.h"
#include <QTest>

QTEST_GUILESS_MAIN(ExtractLanguageJobTest)
ExtractLanguageJobTest::ExtractLanguageJobTest(QObject *parent)
    : QObject{parent}
{
}

void ExtractLanguageJobTest::shouldHaveDefaultValues()
{
    ExtractLanguageJob w;
    QVERIFY(w.source().isEmpty());
    QVERIFY(!w.canStart());
}

#include "moc_extractlanguagejobtest.cpp"
