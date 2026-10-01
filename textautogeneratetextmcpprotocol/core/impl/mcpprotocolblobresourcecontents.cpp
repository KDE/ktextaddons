/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolblobresourcecontents.h"
#include <QDebug>
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolBlobResourceContents::McpProtocolBlobResourceContents() = default;

bool McpProtocolBlobResourceContents::operator==(const McpProtocolBlobResourceContents &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolBlobResourceContents &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "blob:" << t.blob();
    d.space() << "mimeType:" << t.mimeType();
    d.space() << "uri:" << t.uri();
    return d;
}

McpProtocolBlobResourceContents McpProtocolBlobResourceContents::fromJson(const QJsonObject &obj)
{
    McpProtocolBlobResourceContents contents;
    if (const QJsonValue metaValue = obj.value("_meta"_L1); metaValue.isObject()) {
        contents.setMeta(McpProtocolMeta::fromJson(metaValue.toObject()));
    }
    contents.setBlob(obj.value("blob"_L1).toString());
    if (obj.contains("mimeType"_L1)) {
        contents.setMimeType(obj.value("mimeType"_L1).toString());
    }
    contents.setUri(obj.value("uri"_L1).toString());
    return contents;
}

QJsonObject McpProtocolBlobResourceContents::toJson(const McpProtocolBlobResourceContents &contents)
{
    QJsonObject obj;
    if (contents.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*contents.meta());
    }
    obj["blob"_L1] = contents.blob();
    obj["uri"_L1] = contents.uri();
    if (contents.mimeType().has_value()) {
        obj["mimeType"_L1] = *contents.mimeType();
    }
    return obj;
}

std::optional<McpProtocolMeta> McpProtocolBlobResourceContents::meta() const
{
    return mMeta;
}

void McpProtocolBlobResourceContents::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

QString McpProtocolBlobResourceContents::blob() const
{
    return mBlob;
}

void McpProtocolBlobResourceContents::setBlob(const QString &newBlob)
{
    mBlob = newBlob;
}

std::optional<QString> McpProtocolBlobResourceContents::mimeType() const
{
    return mMimeType;
}

void McpProtocolBlobResourceContents::setMimeType(std::optional<QString> newMimeType)
{
    mMimeType = std::move(newMimeType);
}

QString McpProtocolBlobResourceContents::uri() const
{
    return mUri;
}

void McpProtocolBlobResourceContents::setUri(const QString &newUri)
{
    mUri = newUri;
}
