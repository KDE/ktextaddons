/*
   SPDX-FileCopyrightText: 2021-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "textemoticonscore_export.h"
#include <QSortFilterProxyModel>
#include <TextEmoticonsCore/EmojiModelManager>
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
    Q_PROPERTY(EmojiModelManager::EmojiTone emojiTone READ emojiTone WRITE setEmojiTone NOTIFY emojiToneChanged)

public:
    explicit EmojiSortFilterProxyModel(QObject *parent = nullptr);
    ~EmojiSortFilterProxyModel() override;
    [[nodiscard]] QString category() const;
    void setCategory(const QString &newCategories);

    [[nodiscard]] QStringList recentEmoticons() const;
    void setRecentEmoticons(const QStringList &newRecentEmoticons);

    [[nodiscard]] QString searchIdentifier() const;
    void setSearchIdentifier(const QString &newSearchIdentifier);

    [[nodiscard]] EmojiModelManager::EmojiTone emojiTone() const;
    void setEmojiTone(EmojiModelManager::EmojiTone tone);

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
