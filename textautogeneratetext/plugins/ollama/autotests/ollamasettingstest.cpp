/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamasettingstest.h"

#include "ollamasettings.h"
#include <QTest>
QTEST_GUILESS_MAIN(OllamaSettingsTest)
using namespace Qt::Literals::StringLiterals;
OllamaSettingsTest::OllamaSettingsTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaSettingsTest::shouldHaveDefaultValues()
{
    OllamaSettings w;
    QCOMPARE(w.seed(), 0);
    QCOMPARE(w.temperature(), 0.8);

    QVERIFY(w.currentModel().isEmpty());
    QVERIFY(w.displayName().isEmpty());
    QVERIFY(w.overrideGfxVersion().isEmpty());
    QVERIFY(w.vulkanSupport().isEmpty());
    QCOMPARE(w.serverUrl(), QUrl(u"http://127.0.0.1:11434"_s));
}

#include "moc_ollamasettingstest.cpp"
