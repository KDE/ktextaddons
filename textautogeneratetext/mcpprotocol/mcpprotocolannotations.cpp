/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolannotations.h"
#include <QDebug>
using namespace McpProtocol;
using namespace Qt::Literals::StringLiterals;
McpProtocolAnnotations::McpProtocolAnnotations() = default;

McpProtocolAnnotations::~McpProtocolAnnotations() = default;

bool McpProtocolAnnotations::operator==(const McpProtocolAnnotations &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolAnnotations &t)
{
    return d;
}

McpProtocolAnnotations McpProtocolAnnotations::fromJson(const QJsonObject &obj)
{
    return {};
}

QJsonObject McpProtocolAnnotations::toJson(const McpProtocolAnnotations &annot)
{
    QJsonObject obj;
    // TODO
    return obj;
}

std::optional<double> McpProtocolAnnotations::priority() const
{
    return mPriority;
}

void McpProtocolAnnotations::setPriority(std::optional<double> newPriority)
{
    mPriority = newPriority;
}

std::optional<QString> McpProtocolAnnotations::lastModified() const
{
    return mLastModified;
}

void McpProtocolAnnotations::setLastModified(std::optional<QString> newLastModified)
{
    mLastModified = std::move(newLastModified);
}
