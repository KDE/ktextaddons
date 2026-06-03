/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolurlelicitationrequirederror.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolURLElicitationRequiredError::McpProtocolURLElicitationRequiredError() = default;

McpProtocolURLElicitationRequiredError::~McpProtocolURLElicitationRequiredError() = default;

bool McpProtocolURLElicitationRequiredError::operator==(const McpProtocolURLElicitationRequiredError &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolURLElicitationRequiredError &t)
{
    d.space() << "error: " << t.error();
    d.space() << "id: " << t.id();
    return d;
}

McpProtocolURLElicitationRequiredError McpProtocolURLElicitationRequiredError::fromJson(const QJsonObject &obj)
{
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (!obj.contains("error"_L1)) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Missing required field: error";
        return {};
    }
    McpProtocolURLElicitationRequiredError result;
    if (obj.contains("error"_L1) && obj["error"_L1].isObject()) {
        result.setError(McpProtocolError::fromJson(obj["error"_L1].toObject()));
    }
    if (obj.contains("id"_L1)) {
        result.setId(McpProtocolUtils::requestIdFromJson(obj["id"_L1]));
    }
    return result;
}

QJsonObject McpProtocolURLElicitationRequiredError::toJson(const McpProtocolURLElicitationRequiredError &boolean)
{
    QJsonObject obj;
    obj.insert("error"_L1, McpProtocolError::toJson(boolean.error()));
    obj.insert("jsonrpc"_L1, u"2.0"_s);
    if (boolean.id().has_value()) {
        obj.insert("id"_L1, McpProtocolUtils::requestIdToJson(*boolean.id()));
    }
    return obj;
}

std::optional<McpProtocolUtils::RequestId> McpProtocolURLElicitationRequiredError::id() const
{
    return mId;
}

void McpProtocolURLElicitationRequiredError::setId(std::optional<McpProtocolUtils::RequestId> newId)
{
    mId = std::move(newId);
}

McpProtocolError McpProtocolURLElicitationRequiredError::error() const
{
    return mError;
}

void McpProtocolURLElicitationRequiredError::setError(const McpProtocolError &newError)
{
    mError = newError;
}
