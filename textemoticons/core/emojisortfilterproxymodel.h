/*
   SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "textemoticonscore_export.h"
#include <QSortFilterProxyModel>
#include <memory>
namespace TextEmoticonsCore
{
/**
 * @brief The EmojiProxyModel class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSCORE_EXPORT EmojiSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(QString category READ category WRITE setCategory NOTIFY categoryChanged)
    Q_PROPERTY(QStringList recentEmoticons READ recentEmoticons WRITE setRecentEmoticons NOTIFY recentEmoticonsChanged)
    Q_PROPERTY(EmojiTone emojiTone READ emojiTone WRITE setEmojiTone NOTIFY emojiToneChanged)

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

    explicit EmojiSortFilterProxyModel(QObject *parent = nullptr);
    ~EmojiSortFilterProxyModel() override;
    [[nodiscard]] QString category() const;
    void setCategory(const QString &newCategories);

    [[nodiscard]] QStringList recentEmoticons() const;
    void setRecentEmoticons(const QStringList &newRecentEmoticons);

    [[nodiscard]] QString searchIdentifier() const;
    void setSearchIdentifier(const QString &newSearchIdentifier);

    [[nodiscard]] EmojiSortFilterProxyModel::EmojiTone emojiTone() const;
    void setEmojiTone(EmojiSortFilterProxyModel::EmojiTone tone);

    [[nodiscard]] QString emojiToneSuffix() const;
Q_SIGNALS:
    void categoryChanged();
    void recentEmoticonsChanged();
    void emojiToneChanged();

protected:
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
    [[nodiscard]] bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    class EmojiProxyModelPrivate;
    std::unique_ptr<EmojiProxyModelPrivate> const d;
};
}
