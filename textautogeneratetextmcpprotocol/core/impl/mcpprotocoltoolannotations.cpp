/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltoolannotations.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolToolAnnotations::McpProtocolToolAnnotations() = default;

std::optional<bool> McpProtocolToolAnnotations::destructiveHint() const
{
    return mDestructiveHint;
}

void McpProtocolToolAnnotations::setDestructiveHint(std::optional<bool> newDestructiveHint)
{
    mDestructiveHint = newDestructiveHint;
}

std::optional<bool> McpProtocolToolAnnotations::idempotentHint() const
{
    return mIdempotentHint;
}

void McpProtocolToolAnnotations::setIdempotentHint(std::optional<bool> newIdempotentHint)
{
    mIdempotentHint = newIdempotentHint;
}

std::optional<bool> McpProtocolToolAnnotations::openWorldHint() const
{
    return mOpenWorldHint;
}

void McpProtocolToolAnnotations::setOpenWorldHint(std::optional<bool> newOpenWorldHint)
{
    mOpenWorldHint = newOpenWorldHint;
}

std::optional<bool> McpProtocolToolAnnotations::readOnlyHint() const
{
    return mReadOnlyHint;
}

void McpProtocolToolAnnotations::setReadOnlyHint(std::optional<bool> newReadOnlyHint)
{
    mReadOnlyHint = newReadOnlyHint;
}

std::optional<QString> McpProtocolToolAnnotations::title() const
{
    return mTitle;
}

void McpProtocolToolAnnotations::setTitle(std::optional<QString> newTitle)
{
    mTitle = std::move(newTitle);
}

bool McpProtocolToolAnnotations::operator==(const McpProtocolToolAnnotations &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations &t)
{
    d.space() << "destructiveHint:" << t.destructiveHint();
    d.space() << "idempotentHint:" << t.idempotentHint();
    d.space() << "openWorldHint:" << t.openWorldHint();
    d.space() << "readOnlyHint:" << t.readOnlyHint();
    d.space() << "title:" << t.title();
    return d;
}

McpProtocolToolAnnotations McpProtocolToolAnnotations::fromJson(const QJsonObject &obj)
{
    McpProtocolToolAnnotations toolAnnotations;
    if (const QJsonValue destructiveHintValue = obj.value("destructiveHint"_L1); destructiveHintValue.isBool()) {
        toolAnnotations.setDestructiveHint(destructiveHintValue.toBool());
    }
    if (const QJsonValue idempotentHintValue = obj.value("idempotentHint"_L1); idempotentHintValue.isBool()) {
        toolAnnotations.setIdempotentHint(idempotentHintValue.toBool());
    }
    if (const QJsonValue openWorldHintValue = obj.value("openWorldHint"_L1); openWorldHintValue.isBool()) {
        toolAnnotations.setOpenWorldHint(openWorldHintValue.toBool());
    }
    if (const QJsonValue readOnlyHintValue = obj.value("readOnlyHint"_L1); readOnlyHintValue.isBool()) {
        toolAnnotations.setReadOnlyHint(readOnlyHintValue.toBool());
    }
    if (const QJsonValue titleValue = obj.value("title"_L1); titleValue.isString()) {
        toolAnnotations.setTitle(titleValue.toString());
    }
    return toolAnnotations;
}

QJsonObject McpProtocolToolAnnotations::toJson(const McpProtocolToolAnnotations &toolAnnotations)
{
    QJsonObject obj;
    if (toolAnnotations.destructiveHint().has_value()) {
        obj.insert("destructiveHint"_L1, *toolAnnotations.destructiveHint());
    }
    if (toolAnnotations.idempotentHint().has_value()) {
        obj.insert("idempotentHint"_L1, *toolAnnotations.idempotentHint());
    }
    if (toolAnnotations.openWorldHint().has_value()) {
        obj.insert("openWorldHint"_L1, *toolAnnotations.openWorldHint());
    }
    if (toolAnnotations.readOnlyHint().has_value()) {
        obj.insert("readOnlyHint"_L1, *toolAnnotations.readOnlyHint());
    }
    if (toolAnnotations.title().has_value()) {
        obj.insert("title"_L1, *toolAnnotations.title());
    }
    return obj;
}
