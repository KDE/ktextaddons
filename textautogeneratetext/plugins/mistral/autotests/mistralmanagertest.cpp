/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mistralmanagertest.h"
#include "mistralmanager.h"
#include <QTest>
QTEST_MAIN(MistralManagerTest)
MistralManagerTest::MistralManagerTest(QObject *parent)
    : QObject{parent}
{
}

void MistralManagerTest::shouldHaveDefaultValues()
{
    MistralManager w;
    QVERIFY(w.apiKey().isEmpty());
}
