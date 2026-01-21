/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelsavailableinfostest.h"
#include "ollamacommonmodelsavalableinfos.h"
#include <QTest>
QTEST_GUILESS_MAIN(OllamaModelsAvailableInfosTest)

OllamaModelsAvailableInfosTest::OllamaModelsAvailableInfosTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelsAvailableInfosTest::shouldHaveDefaultValues()
{
    OllamaCommonModelsAvalableInfos infos;
    QVERIFY(infos.infos().isEmpty());
}

#include "moc_ollamamodelsavailableinfostest.cpp"
