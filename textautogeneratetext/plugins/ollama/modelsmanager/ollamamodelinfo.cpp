/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinfo.h"
#include "autogeneratetext_ollama_debug.h"
#include <QJsonArray>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
OllamaModelInfo::OllamaModelInfo() = default;

OllamaModelInfo::~OllamaModelInfo() = default;

bool OllamaModelInfo::isValid() const
{
    return !mName.isEmpty();
}

bool OllamaModelInfo::operator==(const OllamaModelInfo &other) const
{
    return mName == other.name() && mUrl == other.url() && mAuthor == other.author() && mLanguages == other.languages() && mTags == other.tags()
        && mCategories == other.categories();
}

OllamaModelInfo::Categories OllamaModelInfo::categories() const
{
    return mCategories;
}

void OllamaModelInfo::setCategories(const Categories &newCategories)
{
    mCategories = newCategories;
}

QString OllamaModelInfo::description() const
{
    // TODO
    return {};
}

void OllamaModelInfo::parseInfo(const QString &name, const QJsonObject &obj)
{
    mName = name;
    mAuthor = obj["author"_L1].toString();
    mUrl = obj["url"_L1].toString();
    const QVariantList varLst = obj["categories"_L1].toArray().toVariantList();
    for (const auto &v : varLst) {
        mCategories |= convertStringToCategory(v.toString());
    }
    const QJsonArray tagsArrayList = obj["tags"_L1].toArray();
    for (int i = 0; i < tagsArrayList.count(); ++i) {
        const QJsonArray tagsArray = tagsArrayList.at(i).toArray();
        const QVariantList tagInfo = tagsArray.toVariantList();
        if (tagInfo.count() != 2) {
            qCWarning(AUTOGENERATETEXT_OLLAMA_LOG) << "tagInfo different from 2 " << tagInfo;
        } else {
            ModelTag tag;
            tag.tag = tagInfo.at(0).toString();
            tag.size = tagInfo.at(1).toString();
            mTags.append(std::move(tag));
        }
    }
    QStringList lst;
    const auto languages = obj["languages"_L1].toArray().toVariantList();
    for (const auto &l : languages) {
        lst.append(l.toString());
    }
    mLanguages = lst;
}

OllamaModelInfo::Category OllamaModelInfo::convertStringToCategory(const QString &str) const
{
    if (str == "tools"_L1) {
        return Category::Tools;
    } else if (str == "small"_L1) {
        return Category::Small;
    } else if (str == "medium"_L1) {
        return Category::Medium;
    } else if (str == "big"_L1) {
        return Category::Big;
    } else if (str == "huge"_L1) {
        return Category::Huge;
    } else if (str == "multilingual"_L1) {
        return Category::Multilingual;
    } else if (str == "code"_L1) {
        return Category::Code;
    } else if (str == "math"_L1) {
        return Category::Math;
    } else if (str == "vision"_L1) {
        return Category::Vision;
    } else if (str == "embedding"_L1) {
        return Category::Embedding;
    } else if (str == "reasoning"_L1) {
        return Category::Reasoning;
    }
    qCWarning(AUTOGENERATETEXT_OLLAMA_LOG) << "Impossible to convert " << str;
    return Category::Unknown;
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
    d.space() << "categories" << t.categories();
    return d;
}

bool OllamaModelInfo::ModelTag::operator==(const ModelTag &other) const
{
    return tag == other.tag && size == other.size;
}

#include "moc_ollamamodelinfo.cpp"
