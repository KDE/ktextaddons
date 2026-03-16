/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mcpprotocolaudiocontent.h"
#include <QDebug>
using namespace Qt::Literals::StringLiterals;
using namespace McpProtocol;
McpProtocolAudioContent::McpProtocolAudioContent() = default;

McpProtocolAudioContent::~McpProtocolAudioContent() = default;

QByteArray McpProtocolAudioContent::type()
{
    return QByteArrayLiteral("audio");
}

bool McpProtocolAudioContent::operator==(const McpProtocolAudioContent &other) const = default;

QDebug operator<<(QDebug d, const McpProtocol::McpProtocolAudioContent &t)
{
    d.space() << "annotations:" << t.annotations();
    d.space() << "meta:" << t.meta();
    d.space() << "mimetype:" << t.mimeType();
    d.space() << "data:" << t.data();
    return d;
}

std::optional<McpProtocolAnnotations> McpProtocolAudioContent::annotations() const
{
    return mAnnotations;
}

void McpProtocolAudioContent::setAnnotations(std::optional<McpProtocolAnnotations> newAnnotations)
{
    mAnnotations = std::move(newAnnotations);
}

QJsonObject McpProtocolAudioContent::meta() const
{
    return mMeta;
}

void McpProtocolAudioContent::setMeta(const QJsonObject &newMeta)
{
    mMeta = newMeta;
}

McpProtocolAudioContent McpProtocolAudioContent::fromJson(const QJsonObject &obj)
{
    McpProtocolAudioContent audio;
    if (obj.value("type"_L1).toString() != QString::fromLatin1(McpProtocolAudioContent::type())) {
        qWarning() << "McpProtocolAudioContent: type is not correct " << obj.value("type"_L1).toString();
        return {};
    }

    if (obj.contains("annotations"_L1)) {
        audio.setAnnotations(McpProtocolAnnotations::fromJson(obj["annotations"_L1].toObject()));
    }
    if (obj.contains("_meta"_L1)) {
        audio.setMeta(obj["_meta"_L1].toObject());
    }
    audio.setData(obj.value("data"_L1).toString());
    audio.setMimeType(obj.value("mimeType"_L1).toString());
    return audio;
}

bool McpProtocolAudioContent::isValid() const
{
    return !mData.isEmpty() && !mMimeType.isEmpty();
}

QJsonObject McpProtocolAudioContent::toJson(const McpProtocolAudioContent &audio)
{
    QJsonObject obj;
    obj["data"_L1] = audio.data();
    obj["mimeType"_L1] = audio.mimeType();
    obj["type"_L1] = QString::fromLatin1(audio.type());
    if (audio.annotations().has_value()) {
        obj["annotations"_L1] = McpProtocolAnnotations::toJson(*audio.annotations());
    }

    // TODO add meta !
    // TODO
    return obj;
}

QString McpProtocolAudioContent::data() const
{
    return mData;
}

void McpProtocolAudioContent::setData(const QString &newData)
{
    mData = newData;
}

QString McpProtocolAudioContent::mimeType() const
{
    return mMimeType;
}

void McpProtocolAudioContent::setMimeType(const QString &newMimeType)
{
    mMimeType = newMimeType;
}
