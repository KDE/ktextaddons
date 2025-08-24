/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QDebug>
#include <QString>
#include <TextAutoGenerateText/TextAutoGenerateManager>
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelAvailableInfo
{
    Q_GADGET
public:
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

    [[nodiscard]] TextAutoGenerateText::TextAutoGenerateManager::Categories categories() const;
    void setCategories(const TextAutoGenerateText::TextAutoGenerateManager::Categories &newCategories);

    [[nodiscard]] QString description() const;

    [[nodiscard]] bool operator==(const OllamaModelAvailableInfo &other) const;

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

Q_DECLARE_TYPEINFO(OllamaModelAvailableInfo, Q_RELOCATABLE_TYPE);
QDebug operator<<(QDebug d, const OllamaModelAvailableInfo &t);
QDebug operator<<(QDebug d, const OllamaModelAvailableInfo::ModelTag &t);
