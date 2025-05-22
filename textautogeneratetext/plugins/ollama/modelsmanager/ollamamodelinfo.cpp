/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinfo.h"
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
OllamaModelInfo::OllamaModelInfo() = default;

OllamaModelInfo::~OllamaModelInfo() = default;

bool OllamaModelInfo::isValid() const
{
    return !mName.isEmpty();
}

void OllamaModelInfo::parseInfo(const QString &name, const QJsonObject &obj)
{
    mName = name;
    mAuthor = obj["author"_L1].toString();
    mUrl = obj["url"_L1].toString();
    // TODO
}

QString OllamaModelInfo::name() const
{
    return mName;
}

void OllamaModelInfo::setName(const QString &newName)
{
    mName = newName;
}

QString OllamaModelInfo::url() const
{
    return mUrl;
}

void OllamaModelInfo::setUrl(const QString &newUrl)
{
    mUrl = newUrl;
}

QString OllamaModelInfo::author() const
{
    return mAuthor;
}

void OllamaModelInfo::setAuthor(const QString &newAuthor)
{
    mAuthor = newAuthor;
}

QStringList OllamaModelInfo::languages() const
{
    return mLanguages;
}

void OllamaModelInfo::setLanguages(const QStringList &newLanguages)
{
    mLanguages = newLanguages;
}

QList<OllamaModelInfo::ModelTag> OllamaModelInfo::tags() const
{
    return mTags;
}

void OllamaModelInfo::setTags(const QList<ModelTag> &newTags)
{
    mTags = newTags;
}

QDebug operator<<(QDebug d, const OllamaModelInfo::ModelTag &t)
{
    d.space() << "tag:" << t.tag;
    d.space() << "size:" << t.size;
    return d;
}

QDebug operator<<(QDebug d, const OllamaModelInfo &t)
{
    d.space() << "name" << t.name();
    d.space() << "url" << t.url();
    d.space() << "author" << t.author();
    d.space() << "languages" << t.languages();
    d.space() << "tags" << t.tags();
    return d;
}

#include "moc_ollamamodelinfo.cpp"
