/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamautilstest.h"
using namespace Qt::Literals::StringLiterals;

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
    QCOMPARE(OllamaUtils::tagsPath(), u"/api/tags"_s);
    QCOMPARE(OllamaUtils::completionPath(), u"/api/generate"_s);
    QCOMPARE(OllamaUtils::pullPath(), u"/api/pull"_s);
    QCOMPARE(OllamaUtils::versionPath(), u"/api/version"_s);
    QCOMPARE(OllamaUtils::modelInfoPath(), u"/api/show"_s);
    QCOMPARE(OllamaUtils::chatPath(), u"/api/chat"_s);
    QCOMPARE(OllamaUtils::deletePath(), u"/api/delete"_s);
    QCOMPARE(OllamaUtils::createPath(), u"/api/create"_s);
}

#include "moc_ollamautilstest.cpp"
