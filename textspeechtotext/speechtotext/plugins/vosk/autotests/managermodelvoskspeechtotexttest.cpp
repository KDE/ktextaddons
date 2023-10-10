/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "managermodelvoskspeechtotexttest.h"
#include "managermodelvoskspeechtotext.h"
#include <QStandardPaths>
#include <QTest>
QTEST_MAIN(ManagerModelVoskSpeechToTextTest)
ManagerModelVoskSpeechToTextTest::ManagerModelVoskSpeechToTextTest(QObject *parent)
    : QObject{parent}
{
    QStandardPaths::setTestModeEnabled(true);
}

void ManagerModelVoskSpeechToTextTest::shouldHaveDefaultValues()
{
    ManagerModelVoskSpeechToText w;
    QVERIFY(w.speechToTextInfos().isEmpty());
    QVERIFY(w.needDownloadModelList());
}

void ManagerModelVoskSpeechToTextTest::shouldLoadModelList_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<int>("numberOfTranslator");
    QTest::newRow("empty") << QStringLiteral("empty") << 0;
    QTest::newRow("fullmodels") << QStringLiteral("model-list") << 106;
    // 1 correct 1 invalid
    QTest::newRow("invalid") << QStringLiteral("invalid") << 1;
}

void ManagerModelVoskSpeechToTextTest::shouldLoadModelList()
{
    QFETCH(QString, fileName);
    QFETCH(int, numberOfTranslator);
    const QString originalJsonFile = QLatin1String(VOSK_DATA_DIR) + QStringLiteral("/modellanguages/") + fileName + QStringLiteral(".json");
    ManagerModelVoskSpeechToText w;
    w.loadModelList(originalJsonFile);
    QCOMPARE(w.speechToTextInfos().count(), numberOfTranslator);
}

#include "moc_managermodelvoskspeechtotexttest.cpp"
