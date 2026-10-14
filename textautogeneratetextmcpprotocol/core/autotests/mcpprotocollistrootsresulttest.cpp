/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollistrootsresulttest.h"
#include <QJsonArray>
#include <QJsonObject>
#include <QTest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListRootsResult>

QTEST_GUILESS_MAIN(McpProtocolListRootsResultTest)

McpProtocolListRootsResultTest::McpProtocolListRootsResultTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolListRootsResultTest::shouldHaveDefaultValues()
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolListRootsResult request;
    QVERIFY(request.roots().isEmpty());
}

void McpProtocolListRootsResultTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolListRootsResult;
    using namespace Qt::Literals::StringLiterals;
    QJsonObject validItem;
    validItem["uri"_L1] = u"file:///home/user"_s;
    QJsonObject valid;
    valid["roots"_L1] = QJsonArray{validItem, QJsonObject()};
    const McpProtocolListRootsResult result = McpProtocolListRootsResult::fromJson(valid);
    // Invalid item is skipped
    QCOMPARE(result.roots().count(), 1);

    QJsonObject obj = valid;
    obj.remove(u"roots"_s);
    QCOMPARE(McpProtocolListRootsResult::fromJson(obj), McpProtocolListRootsResult());
}

#include "moc_mcpprotocollistrootsresulttest.cpp"
