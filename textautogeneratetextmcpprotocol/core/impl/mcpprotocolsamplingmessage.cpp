/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpprotocolsamplingmessage.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolSamplingMessage::McpProtocolSamplingMessage() = default;
McpProtocolSamplingMessage::~McpProtocolSamplingMessage() = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolSamplingMessage &t)
{
    // TODO
    return d;
}

// TODO bool McpProtocolSamplingMessage::operator==(const McpProtocolSamplingMessage &other) const = default;

McpProtocolSamplingMessage McpProtocolSamplingMessage::fromJson(const QJsonObject &obj)
{
    // TODO
    return {};
}

QJsonObject McpProtocolSamplingMessage::toJson(const McpProtocolSamplingMessage &image)
{
    // TODO
    return {};
}
