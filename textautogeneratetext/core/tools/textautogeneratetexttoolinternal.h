/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QList>
#include <TextAutoGenerateText/TextAutoGenerateTextToolInternalProperty>
class QDebug;
class QJsonObject;
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToolInternal
{
public:
    /*!
     */
    TextAutoGenerateTextToolInternal();
    /*!
     */
    ~TextAutoGenerateTextToolInternal();

    /*!
     */
    [[nodiscard]] QList<TextAutoGenerateTextToolInternalProperty> properties() const;
    /*!
     */
    void setProperties(const QList<TextAutoGenerateTextToolInternalProperty> &newProperties);

    /*!
     */
    [[nodiscard]] QStringList required() const;
    /*!
     */
    void setRequired(const QStringList &newRequired);

    /*!
     */
    [[nodiscard]] QByteArray toolNameId() const;
    /*!
     */
    void setToolNameId(const QByteArray &newToolNameId);

    /*!
     */
    [[nodiscard]] QJsonObject generateMetadata() const;

    /*!
     */
    [[nodiscard]] QString description() const;
    /*!
     */
    void setDescription(const QString &newDescription);

    /*!
     */
    void parse(const QJsonObject &obj);

    /*!
     */
    [[nodiscard]] bool operator==(const TextAutoGenerateTextToolInternal &other) const;

private:
    QList<TextAutoGenerateTextToolInternalProperty> mProperties;
    QStringList mRequired;
    QByteArray mToolNameId;
    QString mDescription;
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToolInternal &t);
