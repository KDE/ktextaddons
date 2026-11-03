/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolservertoolarguments.h"
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;

bool McpProtocolServerToolArguments::isProvided(const QJsonValue &value)
{
    return !value.isUndefined() && !value.isNull();
}

std::optional<qint64> McpProtocolServerToolArguments::integer(const QJsonValue &value)
{
    if (value.isDouble()) {
        // toInteger() returns default value when number has a fractional part
        const qint64 result = value.toInteger();
        if (static_cast<double>(result) == value.toDouble()) {
            return result;
        }
        return std::nullopt;
    }
    if (value.isString()) {
        bool ok = false;
        const qint64 result = value.toString().trimmed().toLongLong(&ok);
        if (ok) {
            return result;
        }
    }
    return std::nullopt;
}

std::optional<double> McpProtocolServerToolArguments::number(const QJsonValue &value)
{
    if (value.isDouble()) {
        return value.toDouble();
    }
    if (value.isString()) {
        bool ok = false;
        const double result = value.toString().trimmed().toDouble(&ok);
        if (ok) {
            return result;
        }
    }
    return std::nullopt;
}

std::optional<bool> McpProtocolServerToolArguments::boolean(const QJsonValue &value)
{
    if (value.isBool()) {
        return value.toBool();
    }
    if (value.isString()) {
        if (const QString text = value.toString().trimmed().toLower(); text == "true"_L1 || text == "false"_L1) {
            return text == "true"_L1;
        }
    }
    return std::nullopt;
}

bool McpProtocolServerToolArguments::readStringList(const QJsonValue &value, QStringList &list)
{
    if (!isProvided(value)) {
        return true;
    }
    if (!value.isArray()) {
        return false;
    }
    const QJsonArray array = value.toArray();
    for (const QJsonValue &element : array) {
        if (!element.isString()) {
            return false;
        }
        if (const QString str = element.toString().trimmed(); !str.isEmpty()) {
            list.append(str);
        }
    }
    return true;
}

bool McpProtocolServerToolArguments::readOptionalString(const QMap<QString, QJsonValue> &arguments, const QString &key, std::optional<QString> &result)
{
    const QJsonValue value = arguments.value(key);
    if (!isProvided(value)) {
        return true;
    }
    if (!value.isString()) {
        return false;
    }
    result = value.toString().trimmed();
    return true;
}
