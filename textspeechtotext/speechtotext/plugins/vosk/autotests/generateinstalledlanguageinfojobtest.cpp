/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "generateinstalledlanguageinfojobtest.h"
#include "generateinstalledlanguageinfojob.h"
#include <QTest>
QTEST_GUILESS_MAIN(GenerateInstalledLanguageInfoJobTest)

GenerateInstalledLanguageInfoJobTest::GenerateInstalledLanguageInfoJobTest(QObject *parent)
    : QObject(parent)
{
}

void GenerateInstalledLanguageInfoJobTest::shouldHaveDefaultValues()
{
    GenerateInstalledLanguageInfoJob w;
    QVERIFY(!w.canStart());
    QVERIFY(!w.info().isValid());
}

#include "moc_generateinstalledlanguageinfojobtest.cpp"
