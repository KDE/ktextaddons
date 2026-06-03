/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolpaginatedrequest.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolPaginatedRequest::McpProtocolPaginatedRequest() = default;

McpProtocolPaginatedRequest::~McpProtocolPaginatedRequest() = default;

bool McpProtocolPaginatedRequest::operator==(const McpProtocolPaginatedRequest &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolPaginatedRequest &t)
{
    d.space() << "id:" << t.id();
    d.space() << "params:" << t.params();
    return d;
}

McpProtocolPaginatedRequest McpProtocolPaginatedRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolPaginatedRequest prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    prompt.setMethod(obj.value("method"_L1).toString());
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolPaginatedRequestParams::fromJson(obj["params"_L1].toObject()));
    }
    if (obj.contains("id"_L1)) {
        prompt.setId(McpProtocolUtils::requestIdFromJson(obj.value("id"_L1)));
    }
    return prompt;
}

QJsonObject McpProtocolPaginatedRequest::toJson(const McpProtocolPaginatedRequest &boolean)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(boolean.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = boolean.method();
    if (boolean.params().has_value()) {
        obj["params"_L1] = McpProtocolPaginatedRequestParams::toJson(*boolean.params());
    }
    return obj;
}

McpProtocolUtils::RequestId McpProtocolPaginatedRequest::id() const
{
    return mId;
}

void McpProtocolPaginatedRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

std::optional<McpProtocolPaginatedRequestParams> McpProtocolPaginatedRequest::params() const
{
    return mParams;
}

void McpProtocolPaginatedRequest::setParams(std::optional<McpProtocolPaginatedRequestParams> newParams)
{
    mParams = std::move(newParams);
}

QString McpProtocolPaginatedRequest::method() const
{
    return mMethod;
}

void McpProtocolPaginatedRequest::setMethod(const QString &newMethod)
{
    mMethod = newMethod;
}
