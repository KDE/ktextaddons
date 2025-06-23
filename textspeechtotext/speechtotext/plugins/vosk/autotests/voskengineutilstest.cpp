/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "voskengineutilstest.h"
using namespace Qt::Literals::StringLiterals;

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
    QCOMPARE(VoskEngineUtils::storageLanguagePath(), QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation) + u"/vosk-texttospeech"_s);
}

void VoskEngineUtilsTest::shouldDefineRepositoryPath()
{
    QCOMPARE(VoskEngineUtils::defaultVoskRepository(), u"https://alphacephei.com/vosk/models/model-list.json"_s);
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
    info.absoluteLanguageModelPath = u"absolute path"_s;
    info.name = u"Name1"_s;
    info.url = u"https://foo.bla.com"_s;
    info.versionStr = u"version"_s;
    const QString pathTest = QStandardPaths::writableLocation(QStandardPaths::GenericDataLocation);
    QVERIFY(VoskEngineUtils::createInstalledLanguageInfo(pathTest, info));

    const VoskEngineUtils::LanguageInstalled loadInfo = VoskEngineUtils::loadInstalledLanguageInfo(pathTest);
    QCOMPARE(loadInfo, info);
}

#include "moc_voskengineutilstest.cpp"
