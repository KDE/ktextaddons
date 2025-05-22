/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QDebug>
#include <QString>
class OllamaModelInfo
{
    Q_GADGET
public:
    enum class Category : uint8_t {
        Unknown,
        Tools,
        Small,
        Medium,
        Big,
        Huge,
        Multilingual,
        Code,
        Math,
    };
    Q_ENUM(Category)

    struct ModelTag {
        QString tag;
        QString size;
    };

    OllamaModelInfo();
    ~OllamaModelInfo();

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

private:
    QString mName;
    QString mUrl;
    QString mAuthor;
    QStringList mLanguages;
    QList<ModelTag> mTags;
};

Q_DECLARE_TYPEINFO(OllamaModelInfo, Q_RELOCATABLE_TYPE);
QDebug operator<<(QDebug d, const OllamaModelInfo &t);
QDebug operator<<(QDebug d, const OllamaModelInfo::ModelTag &t);
