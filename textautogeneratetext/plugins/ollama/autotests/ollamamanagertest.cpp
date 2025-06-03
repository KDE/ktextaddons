/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamamanagertest.h"
#include "ollamamanager.h"
#include <QTest>
QTEST_MAIN(OllamaManagerTest)
OllamaManagerTest::OllamaManagerTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaManagerTest::shouldHaveDefaultValues()
{
    OllamaManager::CreateModelInfo w;
    QVERIFY(w.fromModelName.isEmpty());
    QVERIFY(w.modelName.isEmpty());
    QVERIFY(w.systemPrompt.isEmpty());
    QVERIFY(!w.isValid());
}

#include "moc_ollamamanagertest.cpp"
