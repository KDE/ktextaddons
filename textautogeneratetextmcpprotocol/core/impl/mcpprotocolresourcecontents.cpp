/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolresourcecontents.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolResourceContents::McpProtocolResourceContents() = default;

McpProtocolResourceContents::~McpProtocolResourceContents() = default;

bool McpProtocolResourceContents::operator==(const McpProtocolResourceContents &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceContents &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "mimeType:" << t.mimeType();
    d.space() << "uri:" << t.uri();
    return d;
}

McpProtocolResourceContents McpProtocolResourceContents::fromJson(const QJsonObject &obj)
{
    McpProtocolResourceContents prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    if (obj.contains("mimeType"_L1)) {
        prompt.setMimeType(obj.value("mimeType"_L1).toString());
    }
    prompt.setUri(obj.value("uri"_L1).toString());
    return prompt;
}

QJsonObject McpProtocolResourceContents::toJson(const McpProtocolResourceContents &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    obj["uri"_L1] = boolean.uri();
    if (boolean.mimeType().has_value()) {
        obj["mimeType"_L1] = *boolean.mimeType();
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolResourceContents::meta() const
{
    return mMeta;
}

void McpProtocolResourceContents::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<QString> McpProtocolResourceContents::mimeType() const
{
    return mMimeType;
}

void McpProtocolResourceContents::setMimeType(std::optional<QString> newMimeType)
{
    mMimeType = std::move(newMimeType);
}

QString McpProtocolResourceContents::uri() const
{
    return mUri;
}

void McpProtocolResourceContents::setUri(const QString &newUri)
{
    mUri = newUri;
}
