/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamautilstest.h"
#include "ollamautils.h"
#include <QTest>
QTEST_MAIN(OllamaUtilsTest)

OllamaUtilsTest::OllamaUtilsTest(QObject *parent)
    : QObject{parent}
{
}

OllamaUtilsTest::~OllamaUtilsTest() = default;

void OllamaUtilsTest::shouldHaveUtilsPath()
{
    QCOMPARE(OllamaUtils::tagsPath(), QStringLiteral("/api/tags"));
    QCOMPARE(OllamaUtils::completionPath(), QStringLiteral("/api/generate"));
    QCOMPARE(OllamaUtils::pullPath(), QStringLiteral("/api/pull"));
    QCOMPARE(OllamaUtils::versionPath(), QStringLiteral("/api/version"));
    QCOMPARE(OllamaUtils::modelInfoPath(), QStringLiteral("/api/show"));
    QCOMPARE(OllamaUtils::chatPath(), QStringLiteral("/api/chat"));
    QCOMPARE(OllamaUtils::deletePath(), QStringLiteral("/api/delete"));
}

#include "moc_ollamautilstest.cpp"
