/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "translatorengineloadertest.h"
#include "translator/translatorengineloader.h"
#include <QTest>
QTEST_MAIN(TranslatorEngineLoaderTest)
TranslatorEngineLoaderTest::TranslatorEngineLoaderTest(QObject *parent)
    : QObject{parent}
{
}

void TranslatorEngineLoaderTest::shouldHaveDefaultValues()
{
    TextTranslator::TranslatorEngineLoader w;
    QVERIFY(!w.translatorEngineInfos().isEmpty());
}

#include "moc_translatorengineloadertest.cpp"
