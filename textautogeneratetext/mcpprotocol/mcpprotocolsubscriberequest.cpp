/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolsubscriberequest.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolSubscribeRequest::McpProtocolSubscribeRequest() = default;

McpProtocolSubscribeRequest::~McpProtocolSubscribeRequest() = default;

QByteArray McpProtocolSubscribeRequest::type()
{
    return "resources/subscribe"_ba;
}

bool McpProtocolSubscribeRequest::operator==(const McpProtocolSubscribeRequest &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolSubscribeRequest &t)
{
    d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolSubscribeRequest McpProtocolSubscribeRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolSubscribeRequest prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolSubscribeRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'method' must be 'resources/subscribe', got: " << obj.value("method"_L1).toString();
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolSubscribeRequestParams::fromJson(obj["params"_L1].toObject()));
    }
    if (obj.contains("id"_L1)) {
        prompt.setId(McpProtocolUtils::requestIdFromJson(obj.value("id"_L1)));
    }
    return prompt;
}

QJsonObject McpProtocolSubscribeRequest::toJson(const McpProtocolSubscribeRequest &boolean)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(boolean.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolSubscribeRequest::type());
    obj["params"_L1] = McpProtocolSubscribeRequestParams::toJson(boolean.params());
    return obj;
}

McpProtocolUtils::RequestId McpProtocolSubscribeRequest::id() const
{
    return mId;
}

void McpProtocolSubscribeRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

McpProtocolSubscribeRequestParams McpProtocolSubscribeRequest::params() const
{
    return mParams;
}

void McpProtocolSubscribeRequest::setParams(const McpProtocolSubscribeRequestParams &newParams)
{
    mParams = newParams;
}
