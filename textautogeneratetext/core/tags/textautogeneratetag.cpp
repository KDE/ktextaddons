/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetag.h"
#include <QCborValue>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUuid>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateTag::TextAutoGenerateTag()
    : mIdentifier(QUuid::createUuid().toByteArray(QUuid::Id128))
{
}

QString TextAutoGenerateTag::name() const
{
    return mName;
}

void TextAutoGenerateTag::setName(const QString &newName)
{
    mName = newName;
}

QByteArray TextAutoGenerateTag::identifier() const
{
    return mIdentifier;
}

void TextAutoGenerateTag::setIdentifier(const QByteArray &newIdentifier)
{
    mIdentifier = newIdentifier;
}

QColor TextAutoGenerateTag::color() const
{
    return mColor;
}

void TextAutoGenerateTag::setColor(const QColor &newColor)
{
    mColor = newColor;
}

bool TextAutoGenerateTag::operator==(const TextAutoGenerateTag &other) const
{
    return other.mIdentifier == mIdentifier && other.mName == mName && other.mColor == mColor;
}

QByteArray TextAutoGenerateTag::serialize(const TextAutoGenerateTag &tag, bool toBinary)
{
    QJsonObject o;
    o["identifier"_L1] = QString::fromLatin1(tag.mIdentifier);
    o["name"_L1] = tag.mName;
    if (tag.mColor.isValid()) {
        o["color"_L1] = tag.mColor.name(QColor::HexArgb);
    }

    if (toBinary) {
        return QCborValue::fromJsonValue(o).toCbor();
    }
    QJsonDocument d;
    d.setObject(o);
    return d.toJson(QJsonDocument::Indented);
}

TextAutoGenerateTag TextAutoGenerateTag::deserialize(const QJsonObject &o)
{
    TextAutoGenerateTag tag;
    tag.setIdentifier(o["identifier"_L1].toString().toLatin1());
    tag.setName(o["name"_L1].toString());
    if (const QString colorName = o["color"_L1].toString(); !colorName.isEmpty()) {
        tag.setColor(QColor::fromString(colorName));
    }
    return tag;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTag &t)
{
    d.space() << "mName" << t.name();
    d.space() << "mIdentifier" << t.identifier();
    d.space() << "mColor" << t.color();
    return d;
}
