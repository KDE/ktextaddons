/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolicon.h"
#include <QDebug>
using namespace McpProtocol;
McpProtocolIcon::McpProtocolIcon() = default;

McpProtocolIcon::~McpProtocolIcon() = default;

bool McpProtocolIcon::operator==(const McpProtocolIcon &other) const = default;

std::optional<QString> McpProtocolIcon::mimeType() const
{
    return mMimeType;
}

void McpProtocolIcon::setMimeType(std::optional<QString> newMimeType)
{
    mMimeType = std::move(newMimeType);
}

std::optional<QStringList> McpProtocolIcon::sizes() const
{
    return mSizes;
}

void McpProtocolIcon::setSizes(std::optional<QStringList> newSizes)
{
    mSizes = std::move(newSizes);
}

std::optional<QString> McpProtocolIcon::theme() const
{
    return mTheme;
}

void McpProtocolIcon::setTheme(std::optional<QString> newTheme)
{
    mTheme = std::move(newTheme);
}

QString McpProtocolIcon::src() const
{
    return mSrc;
}

void McpProtocolIcon::setSrc(const QString &newSrc)
{
    mSrc = newSrc;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolIcon &t)
{
    d.space() << "src:" << t.src();
    return d;
}

McpProtocolIcon McpProtocolIcon::fromJson(const QJsonObject &obj)
{
    return {};
}

QJsonObject McpProtocolIcon::toJson(const McpProtocolIcon &image)
{
    return {};
}
