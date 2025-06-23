/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "managermodeltranslatortest.h"
using namespace Qt::Literals::StringLiterals;

#include "managermodeltranslator.h"
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
    QTest::newRow("empty") << u"empty"_s << 0;
    QTest::newRow("fullmodels") << u"models"_s << 21;
    // 1 correct 1 invalid
    QTest::newRow("invalid") << u"invalid"_s << 1;
}

void ManagerModelTranslatorTest::shouldParseJson()
{
    QFETCH(QString, fileName);
    QFETCH(int, numberOfTranslator);
    const QString originalJsonFile = QLatin1String(BERGAMOT_DATA_DIR) + u"/modellanguages/"_s + fileName + u".json"_s;
    ManagerModelTranslator w;
    w.loadModelList(originalJsonFile);
    QCOMPARE(w.translators().count(), numberOfTranslator);
}

#include "moc_managermodeltranslatortest.cpp"
