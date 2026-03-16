/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolimagecontent.h"

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
