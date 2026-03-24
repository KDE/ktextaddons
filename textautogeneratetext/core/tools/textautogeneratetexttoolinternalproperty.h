/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QStringList>
class QDebug;
class QJsonObject;
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty
 * \brief The TextAutoGenerateTextToolInternalProperty class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextToolInternalProperty
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToolInternalProperty
{
public:
    /*!
     * \brief TextAutoGenerateTextToolInternalProperty
     */
    TextAutoGenerateTextToolInternalProperty();
    /*!
     */
    ~TextAutoGenerateTextToolInternalProperty();

    /*!
     */
    [[nodiscard]] QStringList typeElements() const;
    /*!
     */
    void setTypeElements(const QStringList &newTypeElements);

    /*!
     */
    [[nodiscard]] QString description() const;
    /*!
     */
    void setDescription(const QString &newDescription);

    /*!
     */
    [[nodiscard]] QString name() const;
    /*!
     */
    void setName(const QString &newName);

    /*!
     */
    void parse(const QJsonObject &obj, const QString &name);

    /*!
     */
    [[nodiscard]] bool isValid() const;

private:
    QStringList mTypeElements;
    QString mDescription;
    QString mName;
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToolInternalProperty &t);
