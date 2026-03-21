/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolblobresourcecontents.h"
#include "textautogeneratetextmcpprotocol_debug.h"
#include <QDebug>
#include <QJsonArray>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolBlobResourceContents::McpProtocolBlobResourceContents() = default;

McpProtocolBlobResourceContents::~McpProtocolBlobResourceContents() = default;

bool McpProtocolBlobResourceContents::operator==(const McpProtocolBlobResourceContents &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolBlobResourceContents &t)
{
    d.space() << "meta:" << t.meta();
    d.space() << "blob:" << t.blob();
    d.space() << "mimeType:" << t.mimeType();
    d.space() << "uri:" << t.uri();
    return d;
}

McpProtocolBlobResourceContents McpProtocolBlobResourceContents::fromJson(const QJsonObject &obj)
{
    McpProtocolBlobResourceContents prompt;
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        prompt.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    prompt.setBlob(obj.value("blob"_L1).toString());
    if (obj.contains("mimeType"_L1)) {
        prompt.setMimeType(obj.value("mimeType"_L1).toString());
    }
    prompt.setUri(obj.value("uri"_L1).toString());
    return prompt;
}

QJsonObject McpProtocolBlobResourceContents::toJson(const McpProtocolBlobResourceContents &boolean)
{
    QJsonObject obj;
    if (boolean.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*boolean.meta());
    }
    obj["blob"_L1] = boolean.blob();
    obj["uri"_L1] = boolean.uri();
    if (boolean.mimeType().has_value()) {
        obj["mimeType"_L1] = *boolean.mimeType();
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
