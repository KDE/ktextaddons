/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelsinfostest.h"
#include "modelsmanager/ollamamodelsinfos.h"
#include <QTest>
QTEST_GUILESS_MAIN(OllamaModelsInfosTest)

OllamaModelsInfosTest::OllamaModelsInfosTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelsInfosTest::shouldHaveDefaultValues()
{
    OllamaModelsInfos infos;
    QVERIFY(infos.infos().isEmpty());
}

#include "moc_ollamamodelsinfostest.cpp"
