/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskextractlanguagejobtest.h"
#include "voskextractlanguagejob.h"
#include <QTest>

QTEST_GUILESS_MAIN(VoskExtractLanguageJobTest)
VoskExtractLanguageJobTest::VoskExtractLanguageJobTest(QObject *parent)
    : QObject{parent}
{
}

void VoskExtractLanguageJobTest::shouldHaveDefaultValues()
{
    VoskExtractLanguageJob w;
    QVERIFY(w.source().isEmpty());
    QVERIFY(!w.canStart());
}

#include "moc_voskextractlanguagejobtest.cpp"
