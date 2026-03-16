/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolimagecontent.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
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

std::optional<McpProtocolAnnotations> McpProtocolImageContent::annotations() const
{
    return mAnnotations;
}

void McpProtocolImageContent::setAnnotations(std::optional<McpProtocolAnnotations> newAnnotations)
{
    mAnnotations = std::move(newAnnotations);
}

QJsonObject McpProtocolImageContent::meta() const
{
    return mMeta;
}

void McpProtocolImageContent::setMeta(const QJsonObject &newMeta)
{
    mMeta = newMeta;
}

bool McpProtocolImageContent::isValid() const
{
    return !mData.isEmpty() && !mMimeType.isEmpty();
}

McpProtocolImageContent McpProtocolImageContent::fromJson(const QJsonObject &obj)
{
    McpProtocolImageContent audio;
    if (obj.value("type"_L1).toString() != QString::fromLatin1(McpProtocolImageContent::type())) {
        qWarning() << "McpProtocolAudioContent: type is not correct " << obj.value("type"_L1).toString();
        return {};
    }
    // TODO
    return {};
}

QJsonObject McpProtocolImageContent::toJson(const McpProtocolImageContent &image)
{
    QJsonObject obj;
    // TODO
    return obj;
}

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolImageContent &t)
{
    d.space() << "data:" << t.data();
    d.space() << "mimeType:" << t.mimeType();
    d.space() << "annotations:" << t.annotations();
    d.space() << "meta:" << t.meta();
    return d;
}
