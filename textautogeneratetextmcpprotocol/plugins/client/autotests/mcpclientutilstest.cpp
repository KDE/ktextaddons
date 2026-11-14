/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientutilstest.h"
#include "mcpclientutils.h"
#include <QTest>
using namespace Qt::Literals::StringLiterals;
QTEST_GUILESS_MAIN(McpClientUtilsTest)

McpClientUtilsTest::McpClientUtilsTest(QObject *parent)
    : QObject{parent}
{
}

void McpClientUtilsTest::shouldParseBearerChallenge_data()
{
    QTest::addColumn<QByteArray>("header");
    QTest::addColumn<bool>("isValid");
    QTest::addColumn<QByteArray>("error");
    QTest::addColumn<QString>("errorDescription");
    QTest::addColumn<QString>("scope");
    QTest::addColumn<QUrl>("resourceMetadata");

    QTest::newRow("empty") << QByteArray() << false << QByteArray() << QString() << QString() << QUrl();
    QTest::newRow("bearer-only") << "Bearer"_ba << true << QByteArray() << QString() << QString() << QUrl();
    QTest::newRow("basic") << "Basic realm=\"foo\""_ba << false << QByteArray() << QString() << QString() << QUrl();
    QTest::newRow("resource-metadata") << "Bearer resource_metadata=\"https://example.com/.well-known/oauth-protected-resource\""_ba << true << QByteArray()
                                       << QString() << QString() << QUrl(u"https://example.com/.well-known/oauth-protected-resource"_s);
    QTest::newRow("full") << "bearer realm=\"mcp\", error=\"insufficient_scope\", scope=\"files:read files:write\", error_description=\"Need \\\"write\\\"\""_ba
                          << true << "insufficient_scope"_ba << u"Need \"write\""_s << u"files:read files:write"_s << QUrl();
    QTest::newRow("unquoted") << "Bearer error=invalid_token,scope=read"_ba << true << "invalid_token"_ba << QString() << u"read"_s << QUrl();
    QTest::newRow("several-challenges") << "Basic realm=\"a\", error=\"other\", Bearer error=\"invalid_token\", Foo error=\"bar\""_ba << true
                                        << "invalid_token"_ba << QString() << QString() << QUrl();
    QTest::newRow("token68") << "Negotiate abc==, Bearer scope=\"x\""_ba << true << QByteArray() << QString() << u"x"_s << QUrl();
    QTest::newRow("unterminated-quote") << "Bearer error=\"invalid"_ba << true << "invalid"_ba << QString() << QString() << QUrl();
}

void McpClientUtilsTest::shouldParseBearerChallenge()
{
    QFETCH(QByteArray, header);
    QFETCH(bool, isValid);
    QFETCH(QByteArray, error);
    QFETCH(QString, errorDescription);
    QFETCH(QString, scope);
    QFETCH(QUrl, resourceMetadata);
    const McpClientUtils::BearerChallenge challenge = McpClientUtils::parseBearerChallenge(header);
    QCOMPARE(challenge.isValid, isValid);
    QCOMPARE(challenge.error, error);
    QCOMPARE(challenge.errorDescription, errorDescription);
    QCOMPARE(challenge.scope, scope);
    QCOMPARE(challenge.resourceMetadata, resourceMetadata);
}

#include "moc_mcpclientutilstest.cpp"
