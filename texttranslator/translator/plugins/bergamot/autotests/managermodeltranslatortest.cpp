/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "managermodeltranslatortest.h"
#include "managermodeltranslator.h"
#include <QJsonDocument>
#include <QTest>
QTEST_MAIN(ManagerModelTranslatorTest)
ManagerModelTranslatorTest::ManagerModelTranslatorTest(QObject *parent)
    : QObject{parent}
{
}

void ManagerModelTranslatorTest::shouldHaveDefaultValues()
{
    ManagerModelTranslator w;
    QVERIFY(w.translators().isEmpty());
    QVERIFY(w.needDownloadModelList());
}

void ManagerModelTranslatorTest::shouldParseJson_data()
{
    QTest::addColumn<QString>("fileName");
    QTest::addColumn<int>("numberOfTranslator");
    QTest::newRow("empty") << QStringLiteral("empty") << 0;
    QTest::newRow("fullmodels") << QStringLiteral("models") << 21;
    // 1 correct 1 invalid
    QTest::newRow("invalid") << QStringLiteral("invalid") << 1;
}

void ManagerModelTranslatorTest::shouldParseJson()
{
    QFETCH(QString, fileName);
    QFETCH(int, numberOfTranslator);
    const QString originalJsonFile = QLatin1String(BERGAMOT_DATA_DIR) + QStringLiteral("/modellanguages/") + fileName + QStringLiteral(".json");
    ManagerModelTranslator w;
    w.loadModelList(originalJsonFile);
    QCOMPARE(w.translators().count(), numberOfTranslator);
}

#include "moc_managermodeltranslatortest.cpp"
