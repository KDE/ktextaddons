/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelavailableinfo.h"
#include "autogeneratetext_ollama_debug.h"
#include "ollamamodelutils.h"
#include <KLocalizedString>
#include <QJsonArray>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
OllamaModelAvailableInfo::OllamaModelAvailableInfo() = default;

OllamaModelAvailableInfo::~OllamaModelAvailableInfo() = default;

bool OllamaModelAvailableInfo::isValid() const
{
    return !mName.isEmpty();
}

bool OllamaModelAvailableInfo::operator==(const OllamaModelAvailableInfo &other) const
{
    return mName == other.name() && mUrl == other.url() && mAuthor == other.author() && mLanguages == other.languages() && mTags == other.tags()
        && mCategories == other.categories();
}

TextAutoGenerateText::TextAutoGenerateManager::Categories OllamaModelAvailableInfo::categories() const
{
    return mCategories;
}

void OllamaModelAvailableInfo::setCategories(const TextAutoGenerateText::TextAutoGenerateManager::Categories &newCategories)
{
    mCategories = newCategories;
}

QString OllamaModelAvailableInfo::description() const
{
    return mDescription;
}

void OllamaModelAvailableInfo::parseInfo(const QString &name, const QJsonObject &obj)
{
    mName = name;
    mAuthor = obj["author"_L1].toString();
    mUrl = obj["url"_L1].toString();
    const QVariantList varLst = obj["categories"_L1].toArray().toVariantList();
    for (const auto &v : varLst) {
        const TextAutoGenerateText::TextAutoGenerateManager::Category c = TextAutoGenerateText::TextAutoGenerateManager::convertStringToCategory(v.toString());
        mCategories |= c;
        mCategoriesName.append(TextAutoGenerateText::TextAutoGenerateManager::convertCategoryToI18n(c));
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
    const auto languageLst = obj["languages"_L1].toArray().toVariantList();
    lst.reserve(languageLst.count());
    for (const auto &l : languageLst) {
        lst.append(l.toString());
    }
    mLanguages = lst;
    mDescription = OllamaModelUtils::description(mName);
}

QStringList OllamaModelAvailableInfo::categoriesName() const
{
    return mCategoriesName;
}

void OllamaModelAvailableInfo::setCategoriesName(const QStringList &newCategoriesName)
{
    mCategoriesName = newCategoriesName;
}

QString OllamaModelAvailableInfo::name() const
{
    return mName;
}

void OllamaModelAvailableInfo::setName(const QString &newName)
{
    mName = newName;
}

QString OllamaModelAvailableInfo::url() const
{
    return mUrl;
}

void OllamaModelAvailableInfo::setUrl(const QString &newUrl)
{
    mUrl = newUrl;
}

QString OllamaModelAvailableInfo::author() const
{
    return mAuthor;
}

void OllamaModelAvailableInfo::setAuthor(const QString &newAuthor)
{
    mAuthor = newAuthor;
}

QStringList OllamaModelAvailableInfo::languages() const
{
    return mLanguages;
}

void OllamaModelAvailableInfo::setLanguages(const QStringList &newLanguages)
{
    mLanguages = newLanguages;
}

QList<OllamaModelAvailableInfo::ModelTag> OllamaModelAvailableInfo::tags() const
{
    return mTags;
}

void OllamaModelAvailableInfo::setTags(const QList<ModelTag> &newTags)
{
    mTags = newTags;
}

QDebug operator<<(QDebug d, const OllamaModelAvailableInfo::ModelTag &t)
{
    d.space() << "tag:" << t.tag;
    d.space() << "size:" << t.size;
    return d;
}

QDebug operator<<(QDebug d, const OllamaModelAvailableInfo &t)
{
    d.space() << "name" << t.name();
    d.space() << "url" << t.url();
    d.space() << "author" << t.author();
    d.space() << "languages" << t.languages();
    d.space() << "tags" << t.tags();
    d.space() << "categories" << t.categories();
    d.space() << "categoriesName" << t.categoriesName();
    return d;
}

bool OllamaModelAvailableInfo::ModelTag::operator==(const ModelTag &other) const
{
    return tag == other.tag && size == other.size;
}

#include "moc_ollamamodelavailableinfo.cpp"
