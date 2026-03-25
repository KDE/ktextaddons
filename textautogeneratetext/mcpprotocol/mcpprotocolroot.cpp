/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolroot.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolRoot::McpProtocolRoot() = default;

McpProtocolRoot::~McpProtocolRoot() = default;

bool McpProtocolRoot::operator==(const McpProtocolRoot &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolRoot &t)
{
    d.space() << "uri:" << t.uri();
    d.space() << "name:" << t.name();
    d.space() << "meta:" << t.meta();
    return d;
}

McpProtocolRoot McpProtocolRoot::fromJson(const QJsonObject &obj)
{
    McpProtocolRoot text;
    if (obj.contains("name"_L1)) {
        text.setName(obj.value("name"_L1).toString());
    }
    text.setUri(obj.value("uri"_L1).toString());
    text.setMeta(McpProtocolMeta::fromJson(obj.value("_meta"_L1).toObject()));
    return text;
}

QJsonObject McpProtocolRoot::toJson(const McpProtocolRoot &text)
{
    QJsonObject obj;
    obj["uri"_L1] = text.uri();
    if (text.name().has_value()) {
        obj["name"_L1] = *text.name();
    }
    if (text.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*text.meta());
    }
    return obj;
}

std::optional<QString> McpProtocolRoot::name() const
{
    return mName;
}

void McpProtocolRoot::setName(std::optional<QString> newName)
{
    mName = std::move(newName);
}

QString McpProtocolRoot::uri() const
{
    return mUri;
}

void McpProtocolRoot::setUri(const QString &newUri)
{
    mUri = newUri;
}

std::optional<McpProtocolMeta> McpProtocolRoot::meta() const
{
    return mMeta;
}

void McpProtocolRoot::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}
