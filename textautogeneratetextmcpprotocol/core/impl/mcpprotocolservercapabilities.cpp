/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolservercapabilities.h"
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateTextMcpProtocolCore;
McpProtocolServerCapabilities::McpProtocolServerCapabilities() = default;

McpProtocolServerCapabilities::~McpProtocolServerCapabilities() = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities &t)
{
    // TODO
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities::Prompts &t)
{
    d.space() << "listChanged:" << t.listChanged();
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities::Resources &t)
{
    d.space() << "listChanged:" << t.listChanged();
    d.space() << "subscribe:" << t.subscribe();
    return d;
}

bool McpProtocolServerCapabilities::operator==(const McpProtocolServerCapabilities &other) const = default;

McpProtocolServerCapabilities McpProtocolServerCapabilities::fromJson(const QJsonObject &obj)
{
    return {};
}

QJsonObject McpProtocolServerCapabilities::toJson(const McpProtocolServerCapabilities &image)
{
    return {};
}

McpProtocolServerCapabilities::Prompts &McpProtocolServerCapabilities::Prompts::listChanged(std::optional<bool> v)
{
    mListChanged = v;
    return *this;
}

const std::optional<bool> &McpProtocolServerCapabilities::Prompts::listChanged() const
{
    return mListChanged;
}
