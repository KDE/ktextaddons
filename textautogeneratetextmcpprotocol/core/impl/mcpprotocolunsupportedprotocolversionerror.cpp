/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolunsupportedprotocolversionerror.h"
#include "textautogeneratetextmcpprotocol_core_debug.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolUnsupportedProtocolVersionError::McpProtocolUnsupportedProtocolVersionError() = default;

bool McpProtocolUnsupportedProtocolVersionError::operator==(const McpProtocolUnsupportedProtocolVersionError &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolUnsupportedProtocolVersionError &t)
{
    d.space() << "error:" << t.error();
    d.space() << "id:" << t.id();
    return d;
}

McpProtocolUnsupportedProtocolVersionError McpProtocolUnsupportedProtocolVersionError::fromJson(const QJsonObject &obj)
{
    if (obj.value("jsonrpc"_L1).toString() != "2.0"_L1) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "Field 'jsonrpc' must be '2.0', got: " << obj.value("jsonrpc"_L1).toString();
        return {};
    }
    if (!obj.value("error"_L1).isObject()) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolUnsupportedProtocolVersionError: missing required field 'error'";
        return {};
    }
    McpProtocolUnsupportedProtocolVersionError result;
    const McpProtocolError error = McpProtocolError::fromJson(obj.value("error"_L1).toObject());
    if (error.code() != errorCode) {
        qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolUnsupportedProtocolVersionError: invalid error code" << error.code();
        return {};
    }
    result.setError(error);
    if (const QJsonValue idValue = obj.value("id"_L1); idValue.isString() || idValue.isDouble()) {
        result.setId(McpProtocolUtils::requestIdFromJson(idValue));
    }
    return result;
}

QJsonObject McpProtocolUnsupportedProtocolVersionError::toJson(const McpProtocolUnsupportedProtocolVersionError &unsupportedProtocolVersionError)
{
    QJsonObject obj;
    obj.insert("error"_L1, McpProtocolError::toJson(unsupportedProtocolVersionError.error()));
    obj.insert("jsonrpc"_L1, u"2.0"_s);
    // JSON-RPC: id is required, null when it can't be determined
    obj.insert("id"_L1,
               unsupportedProtocolVersionError.id().has_value() ? McpProtocolUtils::requestIdToJson(*unsupportedProtocolVersionError.id())
                                                                : QJsonValue(QJsonValue::Null));
    return obj;
}

std::optional<McpProtocolUtils::RequestId> McpProtocolUnsupportedProtocolVersionError::id() const
{
    return mId;
}

void McpProtocolUnsupportedProtocolVersionError::setId(std::optional<McpProtocolUtils::RequestId> newId)
{
    mId = std::move(newId);
}

McpProtocolError McpProtocolUnsupportedProtocolVersionError::error() const
{
    return mError;
}

void McpProtocolUnsupportedProtocolVersionError::setError(const McpProtocolError &newError)
{
    mError = newError;
}

QStringList McpProtocolUnsupportedProtocolVersionError::supported() const
{
    QStringList list;
    const QJsonArray array = mError.data().value_or(QJsonValue()).toObject().value("supported"_L1).toArray();
    list.reserve(array.count());
    for (const QJsonValue &value : array) {
        if (value.isString()) {
            list.append(value.toString());
        } else {
            qCWarning(TEXTAUTOGENERATEMCPPROTOCOLCORE_LOG) << "McpProtocolUnsupportedProtocolVersionError: invalid supported version" << value;
        }
    }
    return list;
}

QString McpProtocolUnsupportedProtocolVersionError::requested() const
{
    return mError.data().value_or(QJsonValue()).toObject().value("requested"_L1).toString();
}
