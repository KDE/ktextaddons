/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolgetpromptrequest.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonObject>

#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolGetPromptRequest::McpProtocolGetPromptRequest() = default;

McpProtocolGetPromptRequest::~McpProtocolGetPromptRequest() = default;

QByteArray McpProtocolGetPromptRequest::type()
{
    return "prompts/get"_ba;
}

bool McpProtocolGetPromptRequest::operator==(const McpProtocolGetPromptRequest &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolGetPromptRequest &t)
{
    d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolGetPromptRequest McpProtocolGetPromptRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolGetPromptRequest prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolGetPromptRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'method' must be 'notifications/progress', got: " << obj.value("method"_L1).toString();
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolGetPromptRequestParams::fromJson(obj["params"_L1].toObject()));
    }
    if (obj.contains("id"_L1)) {
        prompt.setId(McpProtocolUtils::requestIdFromJson(obj.value("id"_L1)));
    }
    return prompt;
}

QJsonObject McpProtocolGetPromptRequest::toJson(const McpProtocolGetPromptRequest &boolean)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(boolean.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolGetPromptRequest::type());
    obj["params"_L1] = McpProtocolGetPromptRequestParams::toJson(boolean.params());
    return obj;
}

McpProtocolUtils::RequestId McpProtocolGetPromptRequest::id() const
{
    return mId;
}

void McpProtocolGetPromptRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

McpProtocolGetPromptRequestParams McpProtocolGetPromptRequest::params() const
{
    return mParams;
}

void McpProtocolGetPromptRequest::setParams(const McpProtocolGetPromptRequestParams &newParams)
{
    mParams = newParams;
}
