/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltoolannotations.h"
#include <QDebug>
#include <QJsonObject>

using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolToolAnnotations::McpProtocolToolAnnotations() = default;

McpProtocolToolAnnotations::~McpProtocolToolAnnotations() = default;

bool McpProtocolToolAnnotations::destructiveHint() const
{
    return mDestructiveHint;
}

void McpProtocolToolAnnotations::setDestructiveHint(bool newDestructiveHint)
{
    mDestructiveHint = newDestructiveHint;
}

bool McpProtocolToolAnnotations::idempotentHint() const
{
    return mIdempotentHint;
}

void McpProtocolToolAnnotations::setIdempotentHint(bool newIdempotentHint)
{
    mIdempotentHint = newIdempotentHint;
}

bool McpProtocolToolAnnotations::openWorldHint() const
{
    return mOpenWorldHint;
}

void McpProtocolToolAnnotations::setOpenWorldHint(bool newOpenWorldHint)
{
    mOpenWorldHint = newOpenWorldHint;
}

bool McpProtocolToolAnnotations::readOnlyHint() const
{
    return mReadOnlyHint;
}

void McpProtocolToolAnnotations::setReadOnlyHint(bool newReadOnlyHint)
{
    mReadOnlyHint = newReadOnlyHint;
}

QString McpProtocolToolAnnotations::title() const
{
    return mTitle;
}

void McpProtocolToolAnnotations::setTitle(const QString &newTitle)
{
    mTitle = newTitle;
}

bool McpProtocolToolAnnotations::operator==(const McpProtocolToolAnnotations &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolToolAnnotations &t)
{
    d.space() << "destructiveHint:" << t.destructiveHint();
    d.space() << "idempotentHint:" << t.idempotentHint();
    d.space() << "openWorldHint:" << t.openWorldHint();
    d.space() << "readOnlyHint:" << t.readOnlyHint();
    d.space() << "title:" << t.title();
    return d;
}

McpProtocolToolAnnotations McpProtocolToolAnnotations::fromJson(const QJsonObject &obj)
{
    McpProtocolToolAnnotations toolAnnotations;
    if (obj.contains("destructiveHint"_L1)) {
        toolAnnotations.setDestructiveHint(obj.value("destructiveHint"_L1).toBool());
    }
    if (obj.contains("idempotentHint"_L1)) {
        toolAnnotations.setIdempotentHint(obj.value("idempotentHint"_L1).toBool());
    }
    if (obj.contains("openWorldHint"_L1)) {
        toolAnnotations.setOpenWorldHint(obj.value("openWorldHint"_L1).toBool());
    }
    if (obj.contains("readOnlyHint"_L1)) {
        toolAnnotations.setReadOnlyHint(obj.value("readOnlyHint"_L1).toBool());
    }
    if (obj.contains("title"_L1)) {
        toolAnnotations.setTitle(obj.value("title"_L1).toString());
    }
    return toolAnnotations;
}

QJsonObject McpProtocolToolAnnotations::toJson(const McpProtocolToolAnnotations &toolAnnotations)
{
    QJsonObject obj;
    obj.insert("destructiveHint"_L1, toolAnnotations.destructiveHint());
    obj.insert("idempotentHint"_L1, toolAnnotations.idempotentHint());
    obj.insert("openWorldHint"_L1, toolAnnotations.openWorldHint());
    obj.insert("readOnlyHint"_L1, toolAnnotations.readOnlyHint());
    obj.insert("title"_L1, toolAnnotations.title());
    return obj;
}
