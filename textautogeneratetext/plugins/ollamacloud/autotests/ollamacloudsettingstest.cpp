/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacloudsettingstest.h"
#include "ollamacloudsettings.h"
#include <QTest>
QTEST_GUILESS_MAIN(OllamaCloudSettingsTest)

OllamaCloudSettingsTest::OllamaCloudSettingsTest(QObject *parent)
    : QObject{parent}
{
}

void OllamaCloudSettingsTest::shouldHaveDefaultValues()
{
    const OllamaCloudSettings settings;
    QVERIFY(settings.currentModel().isEmpty());
    QVERIFY(settings.displayName().isEmpty());
    QVERIFY(settings.serverUrl().isEmpty());
}

#include "moc_ollamacloudsettingstest.cpp"
