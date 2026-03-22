/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolcalltoolrequest.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolCallToolRequest::McpProtocolCallToolRequest() = default;

McpProtocolCallToolRequest::~McpProtocolCallToolRequest() = default;

QByteArray McpProtocolCallToolRequest::type()
{
    return "tools/call"_ba;
}

bool McpProtocolCallToolRequest::operator==(const McpProtocolCallToolRequest &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolCallToolRequest &t)
{
    // TODO d.space() << "id:" << t.id();
    d.space() << "params:" << t.params();
    return d;
}

McpProtocolCallToolRequest McpProtocolCallToolRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolCallToolRequest prompt;
    // TODO
    return prompt;
}

QJsonObject McpProtocolCallToolRequest::toJson(const McpProtocolCallToolRequest &boolean)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocol::McpProtocolUtils::RequestIdToJson(boolean.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolCallToolRequest::type());
    obj["params"_L1] = McpProtocolCallToolRequestParams::toJson(boolean.params());
    return obj;
}

McpProtocolUtils::RequestId McpProtocolCallToolRequest::id() const
{
    return mId;
}

void McpProtocolCallToolRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

McpProtocolCallToolRequestParams McpProtocolCallToolRequest::params() const
{
    return mParams;
}

void McpProtocolCallToolRequest::setParams(const McpProtocolCallToolRequestParams &newParams)
{
    mParams = newParams;
}
