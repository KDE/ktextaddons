/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolimagecontent.h"
#include <QDebug>
#include <QJsonObject>
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

std::optional<McpProtocolMeta> McpProtocolImageContent::meta() const
{
    return mMeta;
}

void McpProtocolImageContent::setMeta(std::optional<McpProtocolMeta> newMeta)
{
    mMeta = std::move(newMeta);
}

bool McpProtocolImageContent::isValid() const
{
    return !mData.isEmpty() && !mMimeType.isEmpty();
}

McpProtocolImageContent McpProtocolImageContent::fromJson(const QJsonObject &obj)
{
    McpProtocolImageContent image;
    if (obj.value("type"_L1).toString() != QString::fromLatin1(McpProtocolImageContent::type())) {
        qWarning() << "McpProtocolAudioContent: type is not correct " << obj.value("type"_L1).toString();
        return {};
    }
    if (obj.contains("_meta"_L1) && obj["_meta"_L1].isObject()) {
        image.setMeta(McpProtocolMeta::fromJson(obj["_meta"_L1].toObject()));
    }
    if (obj.contains("annotations"_L1) && obj["annotations"_L1].isObject()) {
        image.setAnnotations(McpProtocolAnnotations::fromJson(obj["annotations"_L1].toObject()));
    }

    image.setData(obj["data"_L1].toString());
    image.setMimeType(obj["mimeType"_L1].toString());
    return image;
}

QJsonObject McpProtocolImageContent::toJson(const McpProtocolImageContent &image)
{
    QJsonObject obj;
    obj["type"_L1] = QString::fromLatin1(image.type());
    obj["data"_L1] = image.data();
    obj["mimeType"_L1] = image.mimeType();
    if (image.annotations().has_value()) {
        obj["annotations"_L1] = McpProtocolAnnotations::toJson(*image.annotations());
    }
    if (image.meta().has_value()) {
        obj["_meta"_L1] = McpProtocolMeta::toJson(*image.meta());
    }
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
