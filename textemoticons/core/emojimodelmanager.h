/*
   SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

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
/**
 * @brief The EmojiModelManager class
 * @author Laurent Montel <montel@kde.org>
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

    static EmojiModelManager *self();
    [[nodiscard]] TextEmoticonsCore::EmojiModel *emojiModel() const;

    /**
     * @brief Set the settings group name used to store the recent identifiers.
     * @note If not set, the group name is "EmoticonRecentUsed".
     */
    void setRecentSettingsGroupName(const QString &key);

    [[nodiscard]] const QStringList &recentIdentifier() const;
    void setRecentIdentifier(const QStringList &newRecentIdentifier);
    Q_INVOKABLE void addIdentifier(const QString &identifier);

    [[nodiscard]] TextEmoticonsCore::CustomEmojiIconManager *customEmojiIconManager() const;
    void setCustomEmojiIconManager(TextEmoticonsCore::CustomEmojiIconManager *newCustomEmojiIconManager);

    [[nodiscard]] QStringList excludeEmoticons() const;
    void setExcludeEmoticons(const QStringList &emoticons);

    [[nodiscard]] EmojiModelManager::EmojiTone emojiTone() const;
    void setEmojiTone(EmojiModelManager::EmojiTone tone);

Q_SIGNALS:
    void usedIdentifierChanged(const QStringList &lst);
    void excludeEmoticonsChanged();
    void emojiToneChanged();

protected:
    explicit EmojiModelManager(QObject *parent = nullptr);
    ~EmojiModelManager() override;

private:
    class EmojiModelManagerPrivate;
    std::unique_ptr<EmojiModelManagerPrivate> const d;
};
}
