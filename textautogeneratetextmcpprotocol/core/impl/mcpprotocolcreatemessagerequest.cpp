/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcreatemessagerequest.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolCreateMessageRequest::McpProtocolCreateMessageRequest() = default;

McpProtocolCreateMessageRequest::~McpProtocolCreateMessageRequest() = default;

QByteArray McpProtocolCreateMessageRequest::type()
{
    return "sampling/createMessage"_ba;
}

// TODO bool McpProtocolCreateMessageRequest::operator==(const McpProtocolCreateMessageRequest &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequest &t)
{
    d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolCreateMessageRequest McpProtocolCreateMessageRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolCreateMessageRequest prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolCreateMessageRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'method' must be 'notifications/progress', got: " << obj.value("method"_L1).toString();
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolCreateMessageRequestParams::fromJson(obj["params"_L1].toObject()));
    }
    if (obj.contains("id"_L1)) {
        prompt.setId(McpProtocolUtils::requestIdFromJson(obj.value("id"_L1)));
    }
    return prompt;
}

QJsonObject McpProtocolCreateMessageRequest::toJson(const McpProtocolCreateMessageRequest &request)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(request.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolCreateMessageRequest::type());
    obj["params"_L1] = McpProtocolCreateMessageRequestParams::toJson(request.params());
    return obj;
}

McpProtocolUtils::RequestId McpProtocolCreateMessageRequest::id() const
{
    return mId;
}

void McpProtocolCreateMessageRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

McpProtocolCreateMessageRequestParams McpProtocolCreateMessageRequest::params() const
{
    return mParams;
}

void McpProtocolCreateMessageRequest::setParams(const McpProtocolCreateMessageRequestParams &newParams)
{
    mParams = newParams;
}
