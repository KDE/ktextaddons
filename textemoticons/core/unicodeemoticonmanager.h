/*
SPDX-FileCopyrightText: 2020-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "emoticoncategory.h"
#include "textemoticonscore_export.h"
#include "unicodeemoticon.h"
#include <QObject>

class UnicodeEmoticonManagerTest;

namespace TextEmoticonsCore
{
class UnicodeEmoticonManagerPrivate;
/*!
 * \class TextEmoticonsCore::UnicodeEmoticonManager
 * \inmodule TextEmoticonsCore
 * \inheaderfile TextEmoticonsCore/UnicodeEmoticonManager
 *
 * \brief The UnicodeEmoticonManager class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSCORE_EXPORT UnicodeEmoticonManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(QList<TextEmoticonsCore::EmoticonCategory> categories READ categories CONSTANT)

public:
    /*!
     * \brief Returns the singleton instance of UnicodeEmoticonManager
     * \param filename The path to the emoticon data file (optional)
     * \return A pointer to the UnicodeEmoticonManager singleton
     */
    static UnicodeEmoticonManager *self(const QString &filename = {});

    /*!
     * \brief Returns the list of all Unicode emoticons
     * \return A list of UnicodeEmoticon objects
     */
    [[nodiscard]] QList<UnicodeEmoticon> unicodeEmojiList() const;

    /*!
     * \brief Returns emoticons in the specified category
     * \param category The category identifier
     * \return A list of UnicodeEmoticon objects in this category
     */
    [[nodiscard]] QList<UnicodeEmoticon> emojisForCategory(const QString &category) const;
    /*!
     * \brief Returns all available emoticon categories
     * \return A list of EmoticonCategory objects
     */
    [[nodiscard]] QList<EmoticonCategory> categories() const;
    /*!
     * \brief Finds the emoticon for the given emoji identifier
     * \param emojiIdentifier The emoji identifier to look up
     * \return The UnicodeEmoticon object, or an invalid emoticon if not found
     */
    [[nodiscard]] UnicodeEmoticon unicodeEmoticonForEmoji(const QString &emojiIdentifier) const;
    /*!
     * \brief Returns the total number of emoticons
     * \return The count of emoticons
     */
    [[nodiscard]] int count() const;

protected:
    /*!
     * \brief Constructs a UnicodeEmoticonManager with optional data file
     * \param filename The path to the emoticon data file (optional)
     * \param parent The parent QObject
     */
    explicit UnicodeEmoticonManager(const QString &filename = {}, QObject *parent = nullptr);
    /*!
     * \brief Destroys the UnicodeEmoticonManager
     */
    ~UnicodeEmoticonManager() override;

    friend UnicodeEmoticonManagerTest;

private:
    std::unique_ptr<UnicodeEmoticonManagerPrivate> const d;
};
}
