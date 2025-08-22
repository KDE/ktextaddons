/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QDebug>
#include <QString>
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelAvailableInfo
{
    Q_GADGET
public:
    enum class Category : uint16_t {
        Unknown = 0,
        Tools = 1,
        Small = 2,
        Medium = 4,
        Big = 8,
        Huge = 16,
        Multilingual = 32,
        Code = 64,
        Math = 128,
        Vision = 256,
        Embedding = 512,
        Reasoning = 1024,
    };
    Q_FLAGS(Category Categories)
    Q_DECLARE_FLAGS(Categories, Category)

    struct ModelTag {
        QString tag;
        QString size;
        [[nodiscard]] bool operator==(const ModelTag &other) const;
    };

    OllamaModelAvailableInfo();
    ~OllamaModelAvailableInfo();

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

    [[nodiscard]] Categories categories() const;
    void setCategories(const Categories &newCategories);

    [[nodiscard]] QString description() const;

    [[nodiscard]] bool operator==(const OllamaModelAvailableInfo &other) const;

    [[nodiscard]] static QString convertCategoryToI18n(OllamaModelAvailableInfo::Category cat);

    [[nodiscard]] QStringList categoriesName() const;
    void setCategoriesName(const QStringList &newCategoriesName);

private:
    [[nodiscard]] TEXTAUTOGENERATEOLLAMA_NO_EXPORT Category convertStringToCategory(const QString &str) const;
    QString mName;
    QString mUrl;
    QString mAuthor;
    QString mDescription;
    QStringList mLanguages;
    QList<ModelTag> mTags;
    Categories mCategories = Category::Unknown;
    QStringList mCategoriesName;
};

Q_DECLARE_TYPEINFO(OllamaModelAvailableInfo, Q_RELOCATABLE_TYPE);
QDebug operator<<(QDebug d, const OllamaModelAvailableInfo &t);
QDebug operator<<(QDebug d, const OllamaModelAvailableInfo::ModelTag &t);
