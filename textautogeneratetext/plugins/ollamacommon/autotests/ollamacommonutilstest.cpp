/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonutilstest.h"

#include "ollamacommonutils.h"
#include <QTest>
QTEST_MAIN(OllamaCommonUtilsTest)

using namespace Qt::Literals::StringLiterals;
OllamaCommonUtilsTest::OllamaCommonUtilsTest(QObject *parent)
    : QObject{parent}
{
}

OllamaCommonUtilsTest::~OllamaCommonUtilsTest() = default;

void OllamaCommonUtilsTest::shouldHaveUtilsPath()
{
    QCOMPARE(OllamaCommonUtils::tagsPath(), u"/api/tags"_s);
    QCOMPARE(OllamaCommonUtils::completionPath(), u"/api/generate"_s);
    QCOMPARE(OllamaCommonUtils::pullPath(), u"/api/pull"_s);
    QCOMPARE(OllamaCommonUtils::versionPath(), u"/api/version"_s);
    QCOMPARE(OllamaCommonUtils::modelInfoPath(), u"/api/show"_s);
    QCOMPARE(OllamaCommonUtils::chatPath(), u"/api/chat"_s);
    QCOMPARE(OllamaCommonUtils::deletePath(), u"/api/delete"_s);
    QCOMPARE(OllamaCommonUtils::createPath(), u"/api/create"_s);
}

#include "moc_ollamacommonutilstest.cpp"
