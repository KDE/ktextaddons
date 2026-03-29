/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltextresourcecontents.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolTextResourceContents::McpProtocolTextResourceContents() = default;

McpProtocolTextResourceContents::~McpProtocolTextResourceContents() = default;

bool McpProtocolTextResourceContents::operator==(const McpProtocolTextResourceContents &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolTextResourceContents &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "mimeType:" << t.mimeType();
    d.space() << "text:" << t.text();
    d.space() << "uri:" << t.uri();
    return d;
}

McpProtocolTextResourceContents McpProtocolTextResourceContents::fromJson(const QJsonObject &obj)
{
    McpProtocolTextResourceContents prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    if (obj.contains("mimeType"_L1)) {
        prompt.setMimeType(obj.value("mimeType"_L1).toString());
    }
    prompt.setText(obj.value("text"_L1).toString());
    prompt.setUri(obj.value("uri"_L1).toString());
    return prompt;
}

QJsonObject McpProtocolTextResourceContents::toJson(const McpProtocolTextResourceContents &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    obj["text"_L1] = boolean.text();
    obj["uri"_L1] = boolean.uri();
    if (boolean.mimeType().has_value()) {
        obj["mimeType"_L1] = *boolean.mimeType();
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolTextResourceContents::meta() const
{
    return mMeta;
}

void McpProtocolTextResourceContents::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

std::optional<QString> McpProtocolTextResourceContents::mimeType() const
{
    return mMimeType;
}

void McpProtocolTextResourceContents::setMimeType(std::optional<QString> newMimeType)
{
    mMimeType = std::move(newMimeType);
}

QString McpProtocolTextResourceContents::text() const
{
    return mText;
}

void McpProtocolTextResourceContents::setText(const QString &newText)
{
    mText = newText;
}

QString McpProtocolTextResourceContents::uri() const
{
    return mUri;
}

void McpProtocolTextResourceContents::setUri(const QString &newUri)
{
    mUri = newUri;
}
