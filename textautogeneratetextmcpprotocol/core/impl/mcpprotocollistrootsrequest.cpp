/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollistrootsrequest.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolListRootsRequest::McpProtocolListRootsRequest() = default;

McpProtocolListRootsRequest::~McpProtocolListRootsRequest() = default;

QByteArray McpProtocolListRootsRequest::type()
{
    return "roots/list"_ba;
}

bool McpProtocolListRootsRequest::operator==(const McpProtocolListRootsRequest &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolListRootsRequest &t)
{
    d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolListRootsRequest McpProtocolListRootsRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolListRootsRequest prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolListRootsRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'method' must be 'notifications/progress', got: " << obj.value("method"_L1).toString();
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolRequestParams::fromJson(obj["params"_L1].toObject()));
    }
    if (obj.contains("id"_L1)) {
        prompt.setId(McpProtocolUtils::requestIdFromJson(obj.value("id"_L1)));
    }
    return prompt;
}

QJsonObject McpProtocolListRootsRequest::toJson(const McpProtocolListRootsRequest &request)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(request.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolListRootsRequest::type());
    if (request.params().has_value()) {
        obj["params"_L1] = McpProtocolRequestParams::toJson(*request.params());
    }
    return obj;
}

McpProtocolUtils::RequestId McpProtocolListRootsRequest::id() const
{
    return mId;
}

void McpProtocolListRootsRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

std::optional<McpProtocolRequestParams> McpProtocolListRootsRequest::params() const
{
    return mParams;
}

void McpProtocolListRootsRequest::setParams(std::optional<McpProtocolRequestParams> newParams)
{
    mParams = std::move(newParams);
}
