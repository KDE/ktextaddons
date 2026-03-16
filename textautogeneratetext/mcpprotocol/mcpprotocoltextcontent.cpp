/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocoltextcontent.h"
#include <QDebug>
using namespace McpProtocol;
McpProtocolTextContent::McpProtocolTextContent() = default;

McpProtocolTextContent::~McpProtocolTextContent() = default;

QByteArray McpProtocolTextContent::type()
{
    return QByteArrayLiteral("text");
}

bool McpProtocolTextContent::operator==(const McpProtocolTextContent &other) const = default;

QString McpProtocolTextContent::text() const
{
    return mText;
}

void McpProtocolTextContent::setText(const QString &newText)
{
    mText = newText;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolTextContent &t)
{
    d.space() << "text:" << t.text();
    d.space() << "annotations:" << t.annotations();
    d.space() << "meta:" << t.meta();
    return d;
}

std::optional<McpProtocolAnnotations> McpProtocolTextContent::annotations() const
{
    return mAnnotations;
}

void McpProtocolTextContent::setAnnotations(std::optional<McpProtocolAnnotations> newAnnotations)
{
    mAnnotations = std::move(newAnnotations);
}

QJsonObject McpProtocolTextContent::meta() const
{
    return mMeta;
}

void McpProtocolTextContent::setMeta(const QJsonObject &newMeta)
{
    mMeta = newMeta;
}

McpProtocolTextContent McpProtocolTextContent::fromJson(const QJsonObject &obj)
{
    return {};
}

QJsonObject McpProtocolTextContent::toJson(const McpProtocolTextContent &image)
{
    return {};
}
