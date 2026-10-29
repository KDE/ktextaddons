/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocoldiscoverresulttest.h"
#include "impl/mcpprotocoldiscoverresult.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolDiscoverResultTest)
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolDiscoverResultTest::McpProtocolDiscoverResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolDiscoverResultTest::shouldHaveDefaultValues()
{
    const McpProtocolDiscoverResult w;
    QVERIFY(!w.meta().has_value());
    QVERIFY(w.supportedVersions().isEmpty());
    QVERIFY(!w.instructions().has_value());
    QCOMPARE(w.ttlMs(), 0);
    QCOMPARE(w.cacheScope(), McpProtocolUtils::CacheScope::Unknown);
}

void McpProtocolDiscoverResultTest::shouldConvertJson()
{
    QJsonObject obj;
    obj["supportedVersions"_L1] = QJsonArray{u"2025-11-25"_s, u"2026-07-28"_s};
    obj["capabilities"_L1] = QJsonObject();
    obj["instructions"_L1] = u"Use the search tool first."_s;
    obj["ttlMs"_L1] = 60000;
    obj["cacheScope"_L1] = u"public"_s;

    const McpProtocolDiscoverResult result = McpProtocolDiscoverResult::fromJson(obj);
    QCOMPARE(result.supportedVersions(), QStringList({u"2025-11-25"_s, u"2026-07-28"_s}));
    QCOMPARE(result.instructions(), u"Use the search tool first."_s);
    QCOMPARE(result.ttlMs(), 60000);
    QCOMPARE(result.cacheScope(), McpProtocolUtils::CacheScope::Public);
    QCOMPARE(McpProtocolDiscoverResult::toJson(result), obj);
}

void McpProtocolDiscoverResultTest::shouldRejectMissingRequiredFields()
{
    QCOMPARE(McpProtocolDiscoverResult::fromJson(QJsonObject()), McpProtocolDiscoverResult());

    QJsonObject obj;
    obj["supportedVersions"_L1] = QJsonArray{u"2026-07-28"_s};
    obj["capabilities"_L1] = QJsonObject();
    obj["ttlMs"_L1] = 0;
    obj["cacheScope"_L1] = u"private"_s;
    QCOMPARE(McpProtocolDiscoverResult::fromJson(obj).cacheScope(), McpProtocolUtils::CacheScope::Private);

    for (const QString &key : {u"supportedVersions"_s, u"capabilities"_s, u"ttlMs"_s, u"cacheScope"_s}) {
        QJsonObject copy = obj;
        copy.remove(key);
        QCOMPARE(McpProtocolDiscoverResult::fromJson(copy), McpProtocolDiscoverResult());
    }

    QJsonObject copy = obj;
    copy["supportedVersions"_L1] = QJsonArray{1};
    QCOMPARE(McpProtocolDiscoverResult::fromJson(copy), McpProtocolDiscoverResult());
    copy = obj;
    copy["ttlMs"_L1] = -1;
    QCOMPARE(McpProtocolDiscoverResult::fromJson(copy), McpProtocolDiscoverResult());
    copy = obj;
    copy["cacheScope"_L1] = u"shared"_s;
    QCOMPARE(McpProtocolDiscoverResult::fromJson(copy), McpProtocolDiscoverResult());
}

#include "moc_mcpprotocoldiscoverresulttest.cpp"
