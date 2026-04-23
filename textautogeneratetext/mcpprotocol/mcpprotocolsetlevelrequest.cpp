/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolsetlevelrequest.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolSetLevelRequest::McpProtocolSetLevelRequest() = default;

McpProtocolSetLevelRequest::~McpProtocolSetLevelRequest() = default;

QByteArray McpProtocolSetLevelRequest::type()
{
    return "logging/setLevel"_ba;
}

bool McpProtocolSetLevelRequest::operator==(const McpProtocolSetLevelRequest &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolSetLevelRequest &t)
{
    d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolSetLevelRequest McpProtocolSetLevelRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolSetLevelRequest prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolSetLevelRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'method' must be 'logging/setLevel', got: " << obj.value("method"_L1).toString();
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolSetLevelRequestParams::fromJson(obj["params"_L1].toObject()));
    }
    if (obj.contains("id"_L1)) {
        prompt.setId(McpProtocolUtils::requestIdFromJson(obj.value("id"_L1)));
    }
    return prompt;
}

QJsonObject McpProtocolSetLevelRequest::toJson(const McpProtocolSetLevelRequest &boolean)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(boolean.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolSetLevelRequest::type());
    obj["params"_L1] = McpProtocolSetLevelRequestParams::toJson(boolean.params());
    return obj;
}

McpProtocolUtils::RequestId McpProtocolSetLevelRequest::id() const
{
    return mId;
}

void McpProtocolSetLevelRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

McpProtocolSetLevelRequestParams McpProtocolSetLevelRequest::params() const
{
    return mParams;
}

void McpProtocolSetLevelRequest::setParams(const McpProtocolSetLevelRequestParams &newParams)
{
    mParams = newParams;
}
