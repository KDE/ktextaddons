/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamacommonmodelavailableinfo.h"
#include "autogeneratetext_ollamacommon_debug.h"
#include "ollamacommonmodelutils.h"
#include <KLocalizedString>
#include <QJsonArray>
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
OllamaCommonModelAvailableInfo::OllamaCommonModelAvailableInfo() = default;

OllamaCommonModelAvailableInfo::~OllamaCommonModelAvailableInfo() = default;

bool OllamaCommonModelAvailableInfo::isValid() const
{
    return !mName.isEmpty();
}

bool OllamaCommonModelAvailableInfo::operator==(const OllamaCommonModelAvailableInfo &other) const
{
    return mName == other.name() && mUrl == other.url() && mAuthor == other.author() && mLanguages == other.languages() && mTags == other.tags()
        && mCategories == other.categories();
}

TextAutoGenerateText::TextAutoGenerateManager::Categories OllamaCommonModelAvailableInfo::categories() const
{
    return mCategories;
}

void OllamaCommonModelAvailableInfo::setCategories(TextAutoGenerateText::TextAutoGenerateManager::Categories newCategories)
{
    mCategories = newCategories;
}

QString OllamaCommonModelAvailableInfo::description() const
{
    return mDescription;
}

void OllamaCommonModelAvailableInfo::parseInfo(const QString &name, const QJsonObject &obj)
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
            qCWarning(AUTOGENERATETEXT_OLLAMACOMMON_LOG) << "tagInfo size different from 2 " << obj;
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
    mDescription = OllamaCommonModelUtils::description(mName);
}

QStringList OllamaCommonModelAvailableInfo::categoriesName() const
{
    return mCategoriesName;
}

void OllamaCommonModelAvailableInfo::setCategoriesName(const QStringList &newCategoriesName)
{
    mCategoriesName = newCategoriesName;
}

QString OllamaCommonModelAvailableInfo::name() const
{
    return mName;
}

void OllamaCommonModelAvailableInfo::setName(const QString &newName)
{
    mName = newName;
}

QString OllamaCommonModelAvailableInfo::url() const
{
    return mUrl;
}

void OllamaCommonModelAvailableInfo::setUrl(const QString &newUrl)
{
    mUrl = newUrl;
}

QString OllamaCommonModelAvailableInfo::author() const
{
    return mAuthor;
}

void OllamaCommonModelAvailableInfo::setAuthor(const QString &newAuthor)
{
    mAuthor = newAuthor;
}

QStringList OllamaCommonModelAvailableInfo::languages() const
{
    return mLanguages;
}

void OllamaCommonModelAvailableInfo::setLanguages(const QStringList &newLanguages)
{
    mLanguages = newLanguages;
}

QList<OllamaCommonModelAvailableInfo::ModelTag> OllamaCommonModelAvailableInfo::tags() const
{
    return mTags;
}

void OllamaCommonModelAvailableInfo::setTags(const QList<ModelTag> &newTags)
{
    mTags = newTags;
}

QDebug operator<<(QDebug d, const OllamaCommonModelAvailableInfo::ModelTag &t)
{
    d.space() << "tag:" << t.tag;
    d.space() << "size:" << t.size;
    return d;
}

QDebug operator<<(QDebug d, const OllamaCommonModelAvailableInfo &t)
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

bool OllamaCommonModelAvailableInfo::ModelTag::operator==(const ModelTag &other) const
{
    return tag == other.tag && size == other.size;
}

#include "moc_ollamacommonmodelavailableinfo.cpp"
