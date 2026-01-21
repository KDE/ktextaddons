/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonmodelavailableinfotest.h"
#include "ollamacommonmodelavailableinfo.h"
#include <QTest>
QTEST_GUILESS_MAIN(OllamaCommonModelAvailableInfoTest)

OllamaCommonModelAvailableInfoTest::OllamaCommonModelAvailableInfoTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaCommonModelAvailableInfoTest::shouldHaveDefaultValues()
{
    OllamaCommonModelAvailableInfo w;
    QVERIFY(w.author().isEmpty());
    QVERIFY(w.name().isEmpty());
    QVERIFY(w.languages().isEmpty());
    QVERIFY(!w.isValid());
}

#include "moc_ollamacommonmodelavailableinfotest.cpp"
