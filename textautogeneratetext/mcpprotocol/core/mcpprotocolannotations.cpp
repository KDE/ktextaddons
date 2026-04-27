/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolannotations.h"
#include <QDebug>
#include <QJsonArray>
#include <QJsonObject>
using namespace TextAutoGenerateTextMcpProtocolCore;
using namespace Qt::Literals::StringLiterals;
McpProtocolAnnotations::McpProtocolAnnotations() = default;

McpProtocolAnnotations::~McpProtocolAnnotations() = default;

bool McpProtocolAnnotations::operator==(const McpProtocolAnnotations &other) const = default;

QDebug operator<<(QDebug d, const TextAutoGenerateTextMcpProtocolCore::McpProtocolAnnotations &t)
{
    d.space() << "audience:" << t.audience();
    d.space() << "priority:" << t.priority();
    d.space() << "lastModified:" << t.lastModified();
    return d;
}

McpProtocolAnnotations McpProtocolAnnotations::fromJson(const QJsonObject &obj)
{
    McpProtocolAnnotations annot;
    if (obj.contains("lastModified"_L1)) {
        annot.setLastModified(obj.value("lastModified"_L1).toString());
    }
    if (obj.contains("priority"_L1)) {
        annot.setPriority(obj.value("priority"_L1).toDouble());
    }
    if (obj.contains("audience"_L1) && obj["audience"_L1].isArray()) {
        const QJsonArray arr = obj["audience"_L1].toArray();
        QList<McpProtocolUtils::Role> audience;
        for (const auto &v : arr) {
            audience.append(McpProtocolUtils::convertRoleFromString(v.toString()));
        }
        annot.setAudience(audience);
    }
    return annot;
}

QJsonObject McpProtocolAnnotations::toJson(const McpProtocolAnnotations &annot)
{
    QJsonObject obj;
    if (annot.audience().has_value()) {
        QJsonArray array;
        const auto audience = *annot.audience();
        for (const auto &v : audience) {
            array.append(McpProtocolUtils::convertRoleToString(v));
        }
        obj["audience"_L1] = array;
    }
    if (annot.lastModified().has_value()) {
        obj["lastModified"_L1] = *annot.lastModified();
    }
    if (annot.priority().has_value()) {
        obj["priority"_L1] = *annot.priority();
    }
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

std::optional<QList<McpProtocolUtils::Role>> McpProtocolAnnotations::audience() const
{
    return mAudience;
}

void McpProtocolAnnotations::setAudience(std::optional<QList<McpProtocolUtils::Role>> newAudience)
{
    mAudience = std::move(newAudience);
}
