/*
   SPDX-FileCopyrightText: 2018-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textemoticonscore_export.h"
#include <QMetaType>
#include <QString>
#include <QStringList>
class QDebug;
namespace TextEmoticonsCore
{
/*!
 * \class TextEmoticonsCore::UnicodeEmoticon
 * \inmodule TextEmoticonsCore
 * \inheaderfile TextEmoticonsCore/UnicodeEmoticon
 *
 * \brief The UnicodeEmoticon class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSCORE_EXPORT UnicodeEmoticon
{
    Q_GADGET
public:
    /*!
     * \brief Constructs an empty UnicodeEmoticon
     */
    UnicodeEmoticon();

    /*!
     * \brief Returns the emoticon identifier
     * \return The identifier string
     */
    [[nodiscard]] QString identifier() const;
    /*!
     * \brief Sets the emoticon identifier
     * \param name The new identifier
     */
    void setIdentifier(const QString &name);

    /*!
     * \brief Returns the Unicode representation of the emoticon
     * \return The Unicode string
     */
    [[nodiscard]] QString unicode() const;
    /*!
     * \brief Returns a display-friendly representation of the Unicode emoticon
     * \return The display string
     */
    [[nodiscard]] QString unicodeDisplay() const;
    /*!
     * \brief Sets the Unicode representation of the emoticon
     * \param unicode The new Unicode string
     */
    void setUnicode(const QString &unicode);

    /*!
     * \brief Returns the emoticon category
     * \return The category string
     */
    [[nodiscard]] QString category() const;
    /*!
     * \brief Sets the emoticon category
     * \param category The new category
     */
    void setCategory(const QString &category);

    /*!
     * \brief Returns the list of aliases for this emoticon
     * \return The list of alternative identifiers
     */
    [[nodiscard]] QStringList aliases() const;
    /*!
     * \brief Sets the list of aliases for this emoticon
     * \param aliases The new list of aliases
     */
    void setAliases(const QStringList &aliases);

    /*!
     * \brief Checks if the emoticon matches the given identifier or alias
     * \param identifier The identifier to check
     * \return true if the emoticon matches this identifier or any alias
     */
    [[nodiscard]] bool hasEmoji(const QString &identifier) const;

    /*!
     * \brief Checks if the emoticon is valid
     * \return true if the emoticon has required data, false otherwise
     */
    [[nodiscard]] bool isValid() const;

    /*!
     * \brief Returns the sort order of the emoticon
     * \return The order value
     */
    [[nodiscard]] int order() const;
    /*!
     * \brief Sets the sort order of the emoticon
     * \param order The new order value
     */
    void setOrder(int order);

    /*!
     * \brief Returns the key for the emoticon
     * \return The key string
     */
    [[nodiscard]] QString key() const;
    /*!
     * \brief Sets the key for the emoticon
     * \param key The new key
     */
    void setKey(const QString &key);

    /*!
     * \brief Compares this emoticon with another for equality
     * \param other The other emoticon to compare
     * \return true if the emoticons are equal
     */
    [[nodiscard]] bool operator==(const UnicodeEmoticon &other) const;

    /*!
     * \brief Sets whether this emoticon has diversity/skin tone variants
     * \param b true if the emoticon has diversity children
     */
    void setDiversityChildren(bool b);
    /*!
     * \brief Checks if this emoticon has diversity/skin tone variants
     * \return true if the emoticon has diversity children
     */
    [[nodiscard]] bool diversityChildren() const;

private:
    QStringList mAliases;
    QString mIdentifier;
    QString mUnicode;
    QString mCategory;
    QString mKey;
    mutable QString mCachedHtml;
    int mOrder = -1;
    bool mHasDiversityChildren = false;
};
}
Q_DECLARE_METATYPE(TextEmoticonsCore::UnicodeEmoticon)
Q_DECLARE_TYPEINFO(TextEmoticonsCore::UnicodeEmoticon, Q_MOVABLE_TYPE);
/*!
 * \brief Outputs the UnicodeEmoticon to a debug stream
 * \param d The debug stream
 * \param t The UnicodeEmoticon to output
 * \return The debug stream
 */
TEXTEMOTICONSCORE_EXPORT QDebug operator<<(QDebug d, const TextEmoticonsCore::UnicodeEmoticon &t);
