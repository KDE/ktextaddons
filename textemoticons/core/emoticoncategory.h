/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textemoticonscore_export.h"
#include <QMetaType>
#include <QString>
class QDebug;
namespace TextEmoticonsCore
{
/*!
 * \class TextEmoticonsCore::EmoticonCategory
 * \inmodule TextEmoticonsCore
 * \inheaderfile TextEmoticonsCore/EmoticonCategory
 *
 * \brief The EmoticonCategory class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSCORE_EXPORT EmoticonCategory
{
    Q_GADGET

    Q_PROPERTY(QString name MEMBER mName CONSTANT)
    Q_PROPERTY(QString category MEMBER mCategory CONSTANT)
    Q_PROPERTY(QString i18nName MEMBER mI18nName CONSTANT)

public:
    /*!
     * \brief Constructs an empty EmoticonCategory
     */
    EmoticonCategory();
    /*!
     * \brief Returns the category name identifier
     * \return The category name
     */
    [[nodiscard]] QString name() const;
    /*!
     * \brief Sets the category name identifier
     * \param name The new category name
     */
    void setName(const QString &name);

    /*!
     * \brief Returns the category identifier
     * \return The category identifier string
     */
    [[nodiscard]] QString category() const;
    /*!
     * \brief Sets the category identifier
     * \param category The new category identifier
     */
    void setCategory(const QString &category);

    /*!
     * \brief Returns the localized category name
     * \return The internationalized category name
     */
    [[nodiscard]] const QString &i18nName() const;

    /*!
     * \brief Sets the localized category name
     * \param newI18nName The new internationalized category name
     */
    void setI18nName(const QString &newI18nName);

    /*!
     * \brief Compares this category with another for ordering
     * \param other The other EmoticonCategory to compare with
     * \return true if this category should be sorted before the other
     */
    [[nodiscard]] bool operator<(const EmoticonCategory &other) const;

    /*!
     * \brief Returns the display order of the category
     * \return The order value
     */
    [[nodiscard]] int order() const;
    /*!
     * \brief Sets the display order of the category
     * \param newOrder The new order value
     */
    void setOrder(int newOrder);

private:
    QString mName;
    QString mCategory;
    QString mI18nName;
    int mOrder = 20;
};
}
Q_DECLARE_METATYPE(TextEmoticonsCore::EmoticonCategory)
Q_DECLARE_TYPEINFO(TextEmoticonsCore::EmoticonCategory, Q_MOVABLE_TYPE);
/*!
 * \brief Outputs the EmoticonCategory to a debug stream
 * \param d The debug stream
 * \param t The EmoticonCategory to output
 * \return The debug stream
 */
TEXTEMOTICONSCORE_EXPORT QDebug operator<<(QDebug d, const TextEmoticonsCore::EmoticonCategory &t);
