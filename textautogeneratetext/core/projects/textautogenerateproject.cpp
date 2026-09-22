/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateproject.h"
#include <QCborValue>
#include <QDebug>
#include <QJsonDocument>
#include <QJsonObject>
#include <QUuid>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateProject::TextAutoGenerateProject()
    : mIdentifier(QUuid::createUuid().toByteArray(QUuid::Id128))
{
}

QString TextAutoGenerateProject::name() const
{
    return mName;
}

void TextAutoGenerateProject::setName(const QString &newName)
{
    mName = newName;
}

QByteArray TextAutoGenerateProject::identifier() const
{
    return mIdentifier;
}

void TextAutoGenerateProject::setIdentifier(const QByteArray &newIdentifier)
{
    mIdentifier = newIdentifier;
}

QColor TextAutoGenerateProject::color() const
{
    return mColor;
}

void TextAutoGenerateProject::setColor(const QColor &newColor)
{
    mColor = newColor;
}

bool TextAutoGenerateProject::operator==(const TextAutoGenerateProject &other) const
{
    return other.mIdentifier == mIdentifier && other.mName == mName && other.mColor == mColor;
}

QByteArray TextAutoGenerateProject::serialize(const TextAutoGenerateProject &project, bool toBinary)
{
    QJsonObject o;
    o["identifier"_L1] = QString::fromLatin1(project.mIdentifier);
    o["name"_L1] = project.mName;
    if (project.mColor.isValid()) {
        o["color"_L1] = project.mColor.name(QColor::HexArgb);
    }

    if (toBinary) {
        return QCborValue::fromJsonValue(o).toCbor();
    }
    QJsonDocument d;
    d.setObject(o);
    return d.toJson(QJsonDocument::Indented);
}

TextAutoGenerateProject TextAutoGenerateProject::deserialize(const QJsonObject &o)
{
    TextAutoGenerateProject project;
    project.setIdentifier(o["identifier"_L1].toString().toLatin1());
    project.setName(o["name"_L1].toString());
    if (const QString colorName = o["color"_L1].toString(); !colorName.isEmpty()) {
        project.setColor(QColor::fromString(colorName));
    }
    return project;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateProject &t)
{
    d.space() << "mName" << t.name();
    d.space() << "mIdentifier" << t.identifier();
    d.space() << "mColor" << t.color();
    return d;
}
