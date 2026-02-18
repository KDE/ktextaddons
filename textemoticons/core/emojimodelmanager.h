/*
   SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "textemoticonscore_export.h"
#include <QObject>
#include <memory>
namespace TextEmoticonsCore
{
class EmojiModel;
class CustomEmojiIconManager;
/*!
 * \class TextEmoticonsCore::EmojiModelManager
 * \inmodule TextEmoticonsCore
 * \inheaderfile TextEmoticonsCore/EmojiModelManager
 *
 * \brief The EmojiModelManager class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSCORE_EXPORT EmojiModelManager : public QObject
{
    Q_OBJECT

    Q_PROPERTY(TextEmoticonsCore::EmojiModel *emojiModel READ emojiModel CONSTANT)
    Q_PROPERTY(QStringList recentIdentifier READ recentIdentifier NOTIFY usedIdentifierChanged)
    Q_PROPERTY(EmojiModelManager::EmojiTone emojiTone READ emojiTone WRITE setEmojiTone NOTIFY emojiToneChanged)

public:
    enum class EmojiTone : uint8_t {
        All, // Show all emoji
        Original, // Show
        Light, // tone1
        MediumLight, // tone2
        Medium, // tone3
        MediumDark, // tone4
        Dark, // tone5
    };
    Q_ENUM(EmojiTone)

    /*!
     * \brief Returns the singleton instance of EmojiModelManager
     * \return A pointer to the EmojiModelManager singleton
     */
    static EmojiModelManager *self();
    /*!
     * \brief Returns the emoji model
     * \return A pointer to the EmojiModel instance
     */
    [[nodiscard]] TextEmoticonsCore::EmojiModel *emojiModel() const;

    /*!
     * \brief Set the settings group name used to store the recent identifiers.
     * \param key The settings group name
     * \note If not set, the group name is "EmoticonRecentUsed".
     */
    void setRecentSettingsGroupName(const QString &key);

    /*!
     * \brief Returns the list of recent identifiers
     * \return A list of recent emoticon identifiers
     */
    [[nodiscard]] const QStringList &recentIdentifier() const;
    /*!
     * \brief Sets the list of recent identifiers
     * \param newRecentIdentifier The new list of recent identifiers
     */
    void setRecentIdentifier(const QStringList &newRecentIdentifier);
    /*!
     * \brief Adds an identifier to the recent identifiers list
     * \param identifier The identifier to add
     */
    Q_INVOKABLE void addIdentifier(const QString &identifier);

    /*!
     * \brief Returns the custom emoji icon manager
     * \return A pointer to the CustomEmojiIconManager instance
     */
    [[nodiscard]] TextEmoticonsCore::CustomEmojiIconManager *customEmojiIconManager() const;
    /*!
     * \brief Sets the custom emoji icon manager
     * \param newCustomEmojiIconManager The new CustomEmojiIconManager instance
     */
    void setCustomEmojiIconManager(TextEmoticonsCore::CustomEmojiIconManager *newCustomEmojiIconManager);

    /*!
     * \brief Returns the list of emoticons to exclude
     * \return A list of emoticon identifiers to exclude from the model
     */
    [[nodiscard]] QStringList excludeEmoticons() const;
    /*!
     * \brief Sets the list of emoticons to exclude
     * \param emoticons The emoticons to exclude
     */
    void setExcludeEmoticons(const QStringList &emoticons);

    /*!
     * \brief Returns the current emoji tone
     * \return The EmojiTone setting
     */
    [[nodiscard]] EmojiModelManager::EmojiTone emojiTone() const;
    /*!
     * \brief Sets the emoji tone
     * \param tone The emoji tone to set
     */
    void setEmojiTone(EmojiModelManager::EmojiTone tone);

Q_SIGNALS:
    /*!
     * \brief Emitted when the used identifier list changes
     * \param lst The new list of recent identifiers
     */
    void usedIdentifierChanged(const QStringList &lst);
    /*!
     * \brief Emitted when the list of excluded emoticons changes
     */
    void excludeEmoticonsChanged();
    /*!
     * \brief Emitted when the emoji tone changes
     */
    void emojiToneChanged();

protected:
    /*!
     * \brief Constructs an EmojiModelManager with the given parent
     * \param parent The parent QObject
     */
    explicit EmojiModelManager(QObject *parent = nullptr);
    /*!
     * \brief Destroys the EmojiModelManager
     */
    ~EmojiModelManager() override;

private:
    class EmojiModelManagerPrivate;
    std::unique_ptr<EmojiModelManagerPrivate> const d;
};
}
