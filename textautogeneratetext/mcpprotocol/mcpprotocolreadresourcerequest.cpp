/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolreadresourcerequest.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolReadResourceRequest::McpProtocolReadResourceRequest() = default;

McpProtocolReadResourceRequest::~McpProtocolReadResourceRequest() = default;

QByteArray McpProtocolReadResourceRequest::type()
{
    return "resources/read"_ba;
}

bool McpProtocolReadResourceRequest::operator==(const McpProtocolReadResourceRequest &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolReadResourceRequest &t)
{
    d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolReadResourceRequest McpProtocolReadResourceRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolReadResourceRequest prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolReadResourceRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'method' must be 'notifications/progress', got: " << obj.value("method"_L1).toString();
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolReadResourceRequestParams::fromJson(obj["params"_L1].toObject()));
    }
    if (obj.contains("id"_L1)) {
        prompt.setId(McpProtocolUtils::requestIdFromJson(obj.value("id"_L1)));
    }
    return prompt;
}

QJsonObject McpProtocolReadResourceRequest::toJson(const McpProtocolReadResourceRequest &boolean)
{
    QJsonObject obj;
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolReadResourceRequest::type());
    obj["params"_L1] = McpProtocolReadResourceRequestParams::toJson(boolean.params());
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(boolean.id());
    return obj;
}

McpProtocolUtils::RequestId McpProtocolReadResourceRequest::id() const
{
    return mId;
}

void McpProtocolReadResourceRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

McpProtocolReadResourceRequestParams McpProtocolReadResourceRequest::params() const
{
    return mParams;
}

void McpProtocolReadResourceRequest::setParams(const McpProtocolReadResourceRequestParams &newParams)
{
    mParams = newParams;
}
