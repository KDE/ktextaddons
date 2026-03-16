/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolimagecontent.h"
#include <QDebug>
using namespace McpProtocol;
McpProtocolImageContent::McpProtocolImageContent() = default;

McpProtocolImageContent::~McpProtocolImageContent() = default;

QByteArray McpProtocolImageContent::type()
{
    return QByteArrayLiteral("image");
}

QString McpProtocolImageContent::mimeType() const
{
    return mMimeType;
}

void McpProtocolImageContent::setMimeType(const QString &newMimeType)
{
    mMimeType = newMimeType;
}

QString McpProtocolImageContent::data() const
{
    return mData;
}

void McpProtocolImageContent::setData(const QString &newData)
{
    mData = newData;
}

bool McpProtocolImageContent::operator==(const McpProtocolImageContent &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolImageContent &t)
{
    d.space() << "data:" << t.data();
    d.space() << "mimeType:" << t.mimeType();
    return d;
}
