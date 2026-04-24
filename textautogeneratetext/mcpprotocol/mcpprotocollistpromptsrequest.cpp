/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollistpromptsrequest.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolListPromptsRequest::McpProtocolListPromptsRequest() = default;

McpProtocolListPromptsRequest::~McpProtocolListPromptsRequest() = default;

QByteArray McpProtocolListPromptsRequest::type()
{
    return "prompts/list"_ba;
}

bool McpProtocolListPromptsRequest::operator==(const McpProtocolListPromptsRequest &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolListPromptsRequest &t)
{
    d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolListPromptsRequest McpProtocolListPromptsRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolListPromptsRequest prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolListPromptsRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'method' must be 'notifications/progress', got: " << obj.value("method"_L1).toString();
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolPaginatedRequestParams::fromJson(obj["params"_L1].toObject()));
    }
    if (obj.contains("id"_L1)) {
        prompt.setId(McpProtocolUtils::requestIdFromJson(obj.value("id"_L1)));
    }
    return prompt;
}

QJsonObject McpProtocolListPromptsRequest::toJson(const McpProtocolListPromptsRequest &boolean)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(boolean.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolListPromptsRequest::type());
    if (boolean.params().has_value()) {
        obj["params"_L1] = McpProtocolPaginatedRequestParams::toJson(*boolean.params());
    }
    return obj;
}

McpProtocolUtils::RequestId McpProtocolListPromptsRequest::id() const
{
    return mId;
}

void McpProtocolListPromptsRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

std::optional<McpProtocolPaginatedRequestParams> McpProtocolListPromptsRequest::params() const
{
    return mParams;
}

void McpProtocolListPromptsRequest::setParams(std::optional<McpProtocolPaginatedRequestParams> newParams)
{
    mParams = std::move(newParams);
}
