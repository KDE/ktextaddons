/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolresourcetemplatereferencetest.h"
#include "impl/mcpprotocolresourcetemplatereference.h"
#include <QJsonObject>
#include <QTest>
QTEST_GUILESS_MAIN(McpProtocolResourceTemplateReferenceTest)
using namespace Qt::Literals::StringLiterals;
McpProtocolResourceTemplateReferenceTest::McpProtocolResourceTemplateReferenceTest(QObject *parent)
    : QObject{parent}
{
}

void McpProtocolResourceTemplateReferenceTest::shouldHaveDefaultValues()
{
    const TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceTemplateReference w;
    QCOMPARE(w.type(), "ref/resource"_ba);
    QVERIFY(w.uri().isEmpty());
}

void McpProtocolResourceTemplateReferenceTest::shouldRejectMissingRequiredFields()
{
    using TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceTemplateReference;
    QJsonObject obj{{"type"_L1, u"ref/resource"_s}, {"uri"_L1, u"file:///{path}"_s}};
    const McpProtocolResourceTemplateReference reference = McpProtocolResourceTemplateReference::fromJson(obj);
    QVERIFY(reference.isValid());
    QCOMPARE(McpProtocolResourceTemplateReference::toJson(reference), obj);
    QVERIFY(!McpProtocolResourceTemplateReference().isValid());
    obj.remove("uri"_L1);
    QCOMPARE(McpProtocolResourceTemplateReference::fromJson(obj), McpProtocolResourceTemplateReference());
}

#include "moc_mcpprotocolresourcetemplatereferencetest.cpp"
