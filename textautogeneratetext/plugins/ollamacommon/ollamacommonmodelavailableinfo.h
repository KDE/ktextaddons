/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollamacommon_export.h"
#include <QString>
#include <TextAutoGenerateText/TextAutoGenerateManager>
class QDebug;
class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonModelAvailableInfo
{
    Q_GADGET
public:
    struct ModelTag {
        QString tag;
        QString size;
        [[nodiscard]] bool operator==(const ModelTag &other) const;
    };

    OllamaCommonModelAvailableInfo();
    ~OllamaCommonModelAvailableInfo();

    [[nodiscard]] QString name() const;
    void setName(const QString &newName);

    [[nodiscard]] QString url() const;
    void setUrl(const QString &newUrl);

    [[nodiscard]] QString author() const;
    void setAuthor(const QString &newAuthor);

    [[nodiscard]] QStringList languages() const;
    void setLanguages(const QStringList &newLanguages);

    [[nodiscard]] QList<ModelTag> tags() const;
    void setTags(const QList<ModelTag> &newTags);

    void parseInfo(const QString &name, const QJsonObject &obj);

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateManager::Categories categories() const;
    void setCategories(TextAutoGenerateText::TextAutoGenerateManager::Categories newCategories);

    [[nodiscard]] QString description() const;

    [[nodiscard]] bool operator==(const OllamaCommonModelAvailableInfo &other) const;

    [[nodiscard]] QStringList categoriesName() const;
    void setCategoriesName(const QStringList &newCategoriesName);

private:
    QString mName;
    QString mUrl;
    QString mAuthor;
    QString mDescription;
    QStringList mLanguages;
    QList<ModelTag> mTags;
    TextAutoGenerateText::TextAutoGenerateManager::Categories mCategories = TextAutoGenerateText::TextAutoGenerateManager::Category::Unknown;
    QStringList mCategoriesName;
};

Q_DECLARE_TYPEINFO(OllamaCommonModelAvailableInfo, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATEOLLAMACOMMON_EXPORT QDebug operator<<(QDebug d, const OllamaCommonModelAvailableInfo &t);
TEXTAUTOGENERATEOLLAMACOMMON_EXPORT QDebug operator<<(QDebug d, const OllamaCommonModelAvailableInfo::ModelTag &t);
