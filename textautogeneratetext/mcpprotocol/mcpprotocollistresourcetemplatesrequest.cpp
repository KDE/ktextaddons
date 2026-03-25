/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocollistresourcetemplatesrequest.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolListResourceTemplatesRequest::McpProtocolListResourceTemplatesRequest() = default;

McpProtocolListResourceTemplatesRequest::~McpProtocolListResourceTemplatesRequest() = default;

QByteArray McpProtocolListResourceTemplatesRequest::type()
{
    return "resources/templates/list"_ba;
}

bool McpProtocolListResourceTemplatesRequest::operator==(const McpProtocolListResourceTemplatesRequest &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolListResourceTemplatesRequest &t)
{
    d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolListResourceTemplatesRequest McpProtocolListResourceTemplatesRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolListResourceTemplatesRequest prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolListResourceTemplatesRequest::type())) {
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

QJsonObject McpProtocolListResourceTemplatesRequest::toJson(const McpProtocolListResourceTemplatesRequest &boolean)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(boolean.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolListResourceTemplatesRequest::type());
    if (boolean.params().has_value()) {
        obj["params"_L1] = McpProtocolPaginatedRequestParams::toJson(*boolean.params());
    }
    return obj;
}

McpProtocolUtils::RequestId McpProtocolListResourceTemplatesRequest::id() const
{
    return mId;
}

void McpProtocolListResourceTemplatesRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

std::optional<McpProtocolPaginatedRequestParams> McpProtocolListResourceTemplatesRequest::params() const
{
    return mParams;
}

void McpProtocolListResourceTemplatesRequest::setParams(std::optional<McpProtocolPaginatedRequestParams> newParams)
{
    mParams = std::move(newParams);
}
