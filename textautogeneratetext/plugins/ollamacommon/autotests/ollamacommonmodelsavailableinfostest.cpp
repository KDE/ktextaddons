/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonmodelsavailableinfostest.h"
#include "ollamacommonmodelsavalableinfos.h"
#include <QTest>
QTEST_GUILESS_MAIN(OllamaCommonModelsAvailableInfosTest)

OllamaCommonModelsAvailableInfosTest::OllamaCommonModelsAvailableInfosTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaCommonModelsAvailableInfosTest::shouldHaveDefaultValues()
{
    OllamaCommonModelsAvalableInfos infos;
    QVERIFY(infos.infos().isEmpty());
}

#include "moc_ollamacommonmodelsavailableinfostest.cpp"
