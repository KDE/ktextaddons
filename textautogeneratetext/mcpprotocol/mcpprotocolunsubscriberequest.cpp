/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolunsubscriberequest.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolUnsubscribeRequest::McpProtocolUnsubscribeRequest() = default;

McpProtocolUnsubscribeRequest::~McpProtocolUnsubscribeRequest() = default;

QByteArray McpProtocolUnsubscribeRequest::type()
{
    return "resources/unsubscribe"_ba;
}

bool McpProtocolUnsubscribeRequest::operator==(const McpProtocolUnsubscribeRequest &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolUnsubscribeRequest &t)
{
    d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolUnsubscribeRequest McpProtocolUnsubscribeRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolUnsubscribeRequest prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolUnsubscribeRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'method' must be 'resources/unsubscribe', got: " << obj.value("method"_L1).toString();
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolUnsubscribeRequestParams::fromJson(obj["params"_L1].toObject()));
    }
    if (obj.contains("id"_L1)) {
        prompt.setId(McpProtocolUtils::requestIdFromJson(obj.value("id"_L1)));
    }
    return prompt;
}

QJsonObject McpProtocolUnsubscribeRequest::toJson(const McpProtocolUnsubscribeRequest &boolean)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(boolean.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolUnsubscribeRequest::type());
    obj["params"_L1] = McpProtocolUnsubscribeRequestParams::toJson(boolean.params());
    return obj;
}

McpProtocolUtils::RequestId McpProtocolUnsubscribeRequest::id() const
{
    return mId;
}

void McpProtocolUnsubscribeRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

McpProtocolUnsubscribeRequestParams McpProtocolUnsubscribeRequest::params() const
{
    return mParams;
}

void McpProtocolUnsubscribeRequest::setParams(const McpProtocolUnsubscribeRequestParams &newParams)
{
    mParams = newParams;
}
