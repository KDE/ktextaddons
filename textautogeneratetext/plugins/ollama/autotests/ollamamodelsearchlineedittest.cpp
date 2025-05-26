/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelsearchlineedittest.h"
#include "modelsmanager/ollamamodelsearchlineedit.h"
#include <QTest>
QTEST_MAIN(OllamaModelSearchLineEditTest)

OllamaModelSearchLineEditTest::OllamaModelSearchLineEditTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaModelSearchLineEditTest::shouldHaveDefaultValues()
{
    OllamaModelSearchLineEdit w;
    // TODO
}

#include "moc_ollamamodelsearchlineedittest.cpp"
