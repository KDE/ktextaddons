/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamasettingstest.h"

#include "ollamasettings.h"
#include <QProcessEnvironment>
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
    QVERIFY(w.rocrVisibleDevice().isEmpty());
    QVERIFY(w.cudaVisibleDevice().isEmpty());
    QVERIFY(w.defaultModelPath().isEmpty());
    QCOMPARE(w.serverUrl(), QUrl(u"http://127.0.0.1:11434"_s));
}

void OllamaSettingsTest::shouldGenerateQProcessEnvironment()
{
    {
        OllamaSettings w;
        w.setCudaVisibleDevice(u"foo1"_s);
        w.setRocrVisibleDevice(u"bla1"_s);
        w.setVulkanSupport(u"kde1"_s);
        w.setOverrideGfxVersion(u"kf6"_s);
        const QStringList variables{
            {u"CUDA_VISIBLE_DEVICES=foo1"_s, u"HSA_OVERRIDE_GFX_VERSION=kf6"_s, u"OLLAMA_VULKAN=kde1"_s, u"ROCR_VISIBLE_DEVICES=bla1"_s}};
        QCOMPARE(w.processEnvironment().toStringList(), variables);
    }
    {
        OllamaSettings w;
        w.setRocrVisibleDevice(u"bla1"_s);
        w.setOverrideGfxVersion(u"kf6"_s);
        const QStringList variables{{u"HSA_OVERRIDE_GFX_VERSION=kf6"_s, u"ROCR_VISIBLE_DEVICES=bla1"_s}};
        QCOMPARE(w.processEnvironment().toStringList(), variables);
    }
}

#include "moc_ollamasettingstest.cpp"
