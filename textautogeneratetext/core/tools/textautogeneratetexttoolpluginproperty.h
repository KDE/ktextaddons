/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <KLazyLocalizedString>
#include <QStringList>
class QDebug;
class QJsonObject;
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty
 * \brief The TextAutoGenerateTextToolPluginProperty class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextToolPluginProperty
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextToolPluginProperty
{
    Q_GADGET
public:
    enum class PropertyType : uint8_t {
        String = 0,
        Number,
        Integer,
        Boolean,
    };
    Q_ENUM(PropertyType)

    /*!
     */
    TextAutoGenerateTextToolPluginProperty();
    /*!
     */
    ~TextAutoGenerateTextToolPluginProperty();

    /*!
     */
    [[nodiscard]] KLazyLocalizedString description() const;
    /*!
     */
    void setDescription(const KLazyLocalizedString &newDescription);

    /*!
     */
    [[nodiscard]] QString name() const;
    /*!
     */
    void setName(const QString &newName);

    /*!
     */
    [[nodiscard]] QStringList typeElements() const;
    /*!
     */
    void setTypeElements(const QStringList &newEnumElements);

    /*!
     */
    [[nodiscard]] PropertyType propertyType() const;
    /*!
     */
    void setPropertyType(PropertyType newPropertyType);

    /*!
     */
    [[nodiscard]] static QString convertPropertyTypeToString(TextAutoGenerateTextToolPluginProperty::PropertyType type);

    /*!
     */
    [[nodiscard]] static TextAutoGenerateTextToolPluginProperty::PropertyType convertPropertyTypeFromString(const QString &str);

private:
    QStringList mTypeElements;
    KLazyLocalizedString mDescription;
    QString mName;
    PropertyType mPropertyType = PropertyType::String;
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty &t);
