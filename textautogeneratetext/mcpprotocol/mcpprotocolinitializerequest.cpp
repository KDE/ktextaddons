/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolinitializerequest.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolInitializeRequest::McpProtocolInitializeRequest() = default;

McpProtocolInitializeRequest::~McpProtocolInitializeRequest() = default;

QByteArray McpProtocolInitializeRequest::type()
{
    return "initialize"_ba;
}

bool McpProtocolInitializeRequest::operator==(const McpProtocolInitializeRequest &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolInitializeRequest &t)
{
    d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolInitializeRequest McpProtocolInitializeRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolInitializeRequest prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolInitializeRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOL_LOG) << "Field 'method' must be 'notifications/progress', got: " << obj.value("method"_L1).toString();
    }
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolInitializeRequestParams::fromJson(obj["params"_L1].toObject()));
    }
    if (obj.contains("id"_L1)) {
        prompt.setId(McpProtocolUtils::requestIdFromJson(obj.value("id"_L1)));
    }
    return prompt;
}

QJsonObject McpProtocolInitializeRequest::toJson(const McpProtocolInitializeRequest &boolean)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(boolean.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolInitializeRequest::type());
    if (boolean.params().has_value()) {
        obj["params"_L1] = McpProtocolInitializeRequestParams::toJson(*boolean.params());
    }
    return obj;
}

McpProtocolUtils::RequestId McpProtocolInitializeRequest::id() const
{
    return mId;
}

void McpProtocolInitializeRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}

std::optional<McpProtocolInitializeRequestParams> McpProtocolInitializeRequest::params() const
{
    return mParams;
}

void McpProtocolInitializeRequest::setParams(std::optional<McpProtocolInitializeRequestParams> newParams)
{
    mParams = std::move(newParams);
}
