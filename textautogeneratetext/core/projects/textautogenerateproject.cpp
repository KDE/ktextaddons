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

bool TextAutoGenerateProject::operator==(const TextAutoGenerateProject &other) const
{
    return other.mIdentifier == mIdentifier && other.mName == mName && other.mIconName == mIconName;
}

QByteArray TextAutoGenerateProject::serialize(const TextAutoGenerateProject &project, bool toBinary)
{
    QJsonObject o;
    o["identifier"_L1] = QString::fromLatin1(project.mIdentifier);
    o["name"_L1] = project.mName;
    if (!project.mIconName.isEmpty()) {
        o["iconName"_L1] = project.mIconName;
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
    if (const QString iconName = o["iconName"_L1].toString(); !iconName.isEmpty()) {
        project.setIconName(iconName);
    }
    return project;
}

QString TextAutoGenerateProject::iconName() const
{
    return mIconName;
}

void TextAutoGenerateProject::setIconName(const QString &newIconName)
{
    mIconName = newIconName;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateProject &t)
{
    d.space() << "mName" << t.name();
    d.space() << "mIdentifier" << t.identifier();
    d.space() << "mIconName" << t.iconName();
    return d;
}
