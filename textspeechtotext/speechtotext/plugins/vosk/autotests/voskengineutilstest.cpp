/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskengineutilstest.h"
#include "voskengineutils.h"
#include <QStandardPaths>
#include <QTest>

QTEST_GUILESS_MAIN(VoskEngineUtilsTest)
VoskEngineUtilsTest::VoskEngineUtilsTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void VoskEngineUtilsTest::shouldDefineStoragePath()
{
    QCOMPARE(VoskEngineUtils::storageLanguagePath(),
             QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + QStringLiteral("/vosk-texttospeech"));
}

void VoskEngineUtilsTest::shouldDefineRepositoryPath()
{
    QCOMPARE(VoskEngineUtils::defaultVoskRepository(), QStringLiteral("https://alphacephei.com/vosk/models/model-list.json"));
}

void VoskEngineUtilsTest::shouldVerifyLanguageInstalledStruct()
{
    VoskEngineUtils::LanguageInstalled info;
    QVERIFY(!info.isValid());
    QVERIFY(info.absoluteLanguageModelPath.isEmpty());
    QVERIFY(info.name.isEmpty());
    QVERIFY(info.url.isEmpty());
    QVERIFY(info.versionStr.isEmpty());
}

void VoskEngineUtilsTest::shouldSaveLoadLanguageInstalled()
{
    VoskEngineUtils::LanguageInstalled info;
    info.absoluteLanguageModelPath = QStringLiteral("absolute path");
    info.name = QStringLiteral("Name1");
    info.url = QStringLiteral("https://foo.bla.com");
    info.versionStr = QStringLiteral("version");
    const QString pathTest = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    QVERIFY(VoskEngineUtils::createInstalledLanguageInfo(pathTest, info));

    const VoskEngineUtils::LanguageInstalled loadInfo = VoskEngineUtils::loadInstalledLanguageInfo(pathTest);
    QCOMPARE(loadInfo, info);
}
