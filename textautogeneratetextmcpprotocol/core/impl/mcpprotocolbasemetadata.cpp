/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolbasemetadata.h"
#include <QDebug>
#include <QJsonObject>
#include <utility>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolBaseMetadata::McpProtocolBaseMetadata() = default;

bool McpProtocolBaseMetadata::operator==(const McpProtocolBaseMetadata &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolBaseMetadata &t)
{
    d.space() << "name:" << t.name();
    d.space() << "title:" << t.title();
    return d;
}

McpProtocolBaseMetadata McpProtocolBaseMetadata::fromJson(const QJsonObject &obj)
{
    McpProtocolBaseMetadata metadata;
    metadata.setName(obj.value("name"_L1).toString());
    if (obj.contains("title"_L1)) {
        metadata.setTitle(obj.value("title"_L1).toString());
    }
    return metadata;
}

QJsonObject McpProtocolBaseMetadata::toJson(const McpProtocolBaseMetadata &metadata)
{
    QJsonObject obj;
    obj["name"_L1] = metadata.name();
    if (metadata.title().has_value()) {
        obj["title"_L1] = *metadata.title();
    }
    return obj;
}

QString McpProtocolBaseMetadata::name() const
{
    return mName;
}

void McpProtocolBaseMetadata::setName(const QString &newName)
{
    mName = newName;
}

std::optional<QString> McpProtocolBaseMetadata::title() const
{
    return mTitle;
}

void McpProtocolBaseMetadata::setTitle(std::optional<QString> newTitle)
{
    mTitle = std::move(newTitle);
}
