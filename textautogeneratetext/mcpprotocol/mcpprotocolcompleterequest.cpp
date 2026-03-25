/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcompleterequest.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolCompleteRequest::McpProtocolCompleteRequest() = default;

McpProtocolCompleteRequest::~McpProtocolCompleteRequest() = default;

QByteArray McpProtocolCompleteRequest::type()
{
    return "completion/complete"_ba;
}

bool McpProtocolCompleteRequest::operator==(const McpProtocolCompleteRequest &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolCompleteRequest &t)
{
    d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    // TODO id
    return d;
}

McpProtocolCompleteRequest McpProtocolCompleteRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolCompleteRequest prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolCompleteRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'method' must be 'notifications/progress', got: " << obj.value("method"_L1).toString();
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolCompleteRequestParams::fromJson(obj["params"_L1].toObject()));
    }
    if (obj.contains("id"_L1)) {
        prompt.setId(McpProtocolUtils::requestIdFromJson(obj.value("id"_L1)));
    }
    return prompt;
}

QJsonObject McpProtocolCompleteRequest::toJson(const McpProtocolCompleteRequest &boolean)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(boolean.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolCompleteRequest::type());
    obj["params"_L1] = McpProtocolCompleteRequestParams::toJson(boolean.params());
    return obj;
}

McpProtocolUtils::RequestId McpProtocolCompleteRequest::id() const
{
    return mId;
}

void McpProtocolCompleteRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

McpProtocolCompleteRequestParams McpProtocolCompleteRequest::params() const
{
    return mParams;
}

void McpProtocolCompleteRequest::setParams(const McpProtocolCompleteRequestParams &newParams)
{
    mParams = newParams;
}
