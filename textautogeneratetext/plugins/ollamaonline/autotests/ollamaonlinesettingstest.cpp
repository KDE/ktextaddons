/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamaonlinesettingstest.h"
#include "ollamaonlinesettings.h"
#include <QTest>
QTEST_GUILESS_MAIN(OllamaOnlineSettingsTest)

OllamaOnlineSettingsTest::OllamaOnlineSettingsTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaOnlineSettingsTest::shouldHaveDefaultValues()
{
    const OllamaOnlineSettings settings;
    QVERIFY(settings.currentModel().isEmpty());
    QVERIFY(settings.displayName().isEmpty());
    QVERIFY(settings.serverUrl().isEmpty());
}

#include "moc_ollamaonlinesettingstest.cpp"
