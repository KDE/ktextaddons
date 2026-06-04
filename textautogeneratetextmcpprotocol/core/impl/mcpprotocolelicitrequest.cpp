/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolelicitrequest.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolElicitRequest::McpProtocolElicitRequest() = default;

McpProtocolElicitRequest::~McpProtocolElicitRequest() = default;

QByteArray McpProtocolElicitRequest::type()
{
    return "elicitation/create"_ba;
}

bool McpProtocolElicitRequest::operator==(const McpProtocolElicitRequest &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequest &t)
{
    // d.space() << "params:" << t.params();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolElicitRequest McpProtocolElicitRequest::fromJson(const QJsonObject &obj)
{
    McpProtocolElicitRequest prompt;

    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (obj.value("method"_L1).toString() != QString::fromLatin1(McpProtocolElicitRequest::type())) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'method' must be 'notifications/progress', got: " << obj.value("method"_L1).toString();
    }
#if 0
    if (obj.contains("params"_L1) && obj["params"_L1].isObject()) {
        prompt.setParams(McpProtocolPaginatedRequestParams::fromJson(obj["params"_L1].toObject()));
    }
#endif
    if (obj.contains("id"_L1)) {
        prompt.setId(McpProtocolUtils::requestIdFromJson(obj.value("id"_L1)));
    }
    return prompt;
}

QJsonObject McpProtocolElicitRequest::toJson(const McpProtocolElicitRequest &boolean)
{
    QJsonObject obj;
    obj["id"_L1] = McpProtocolUtils::requestIdToJson(boolean.id());
    obj["jsonrpc"_L1] = u"2.0"_s;
    obj["method"_L1] = QString::fromLatin1(McpProtocolElicitRequest::type());
#if 0
    if (boolean.params().has_value()) {
        obj["params"_L1] = McpProtocolPaginatedRequestParams::toJson(*boolean.params());
    }
#endif
    return obj;
}

McpProtocolUtils::RequestId McpProtocolElicitRequest::id() const
{
    return mId;
}

void McpProtocolElicitRequest::setId(const McpProtocolUtils::RequestId &newId)
{
    mId = newId;
}
