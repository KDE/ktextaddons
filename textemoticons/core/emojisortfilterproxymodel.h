/*
   SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "textemoticonscore_export.h"
#include <QSortFilterProxyModel>
#include <TextEmoticonsCore/EmojiModelManager>
#include <memory>
namespace TextEmoticonsCore
{
/*!
 * \class TextEmoticonsCore::EmojiSortFilterProxyModel
 * \inmodule TextEmoticonsCore
 * \inheaderfile TextEmoticonsCore/EmojiSortFilterProxyModel
 *
 * \brief The EmojiProxyModel class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSCORE_EXPORT EmojiSortFilterProxyModel : public QSortFilterProxyModel
{
    Q_OBJECT

    Q_PROPERTY(QString category READ category WRITE setCategory NOTIFY categoryChanged)
    Q_PROPERTY(QStringList recentEmoticons READ recentEmoticons WRITE setRecentEmoticons NOTIFY recentEmoticonsChanged)
    Q_PROPERTY(EmojiModelManager::EmojiTone emojiTone READ emojiTone WRITE setEmojiTone NOTIFY emojiToneChanged)

public:
    /*!
     * \brief Constructs an EmojiSortFilterProxyModel with the given parent
     * \param parent The parent QObject
     */
    explicit EmojiSortFilterProxyModel(QObject *parent = nullptr);
    /*!
     * \brief Destroys the EmojiSortFilterProxyModel
     */
    ~EmojiSortFilterProxyModel() override;
    /*!
     * \brief Returns the current category filter
     * \return The emoji category to filter by
     */
    [[nodiscard]] QString category() const;
    /*!
     * \brief Sets the emoji category filter
     * \param newCategories The new category filter
     */
    void setCategory(const QString &newCategories);

    /*!
     * \brief Returns the list of recent emoticons
     * \return A list of recent emoticon identifiers
     */
    [[nodiscard]] QStringList recentEmoticons() const;
    /*!
     * \brief Sets the list of recent emoticons
     * \param newRecentEmoticons The new list of recent emoticons
     */
    void setRecentEmoticons(const QStringList &newRecentEmoticons);

    /*!
     * \brief Returns the search identifier filter
     * \return The search identifier string
     */
    [[nodiscard]] QString searchIdentifier() const;
    /*!
     * \brief Sets the search identifier filter
     * \param newSearchIdentifier The new search identifier
     */
    void setSearchIdentifier(const QString &newSearchIdentifier);

    /*!
     * \brief Returns the current emoji tone setting
     * \return The EmojiTone value
     */
    [[nodiscard]] EmojiModelManager::EmojiTone emojiTone() const;
    /*!
     * \brief Sets the emoji tone
     * \param tone The emoji tone to apply
     */
    void setEmojiTone(EmojiModelManager::EmojiTone tone);

    /*!
     * \brief Returns the emoji tone suffix
     * \return The string suffix for the current emoji tone
     */
    [[nodiscard]] QString emojiToneSuffix() const;
Q_SIGNALS:
    /*!
     * \brief Emitted when the category filter changes
     */
    void categoryChanged();
    /*!
     * \brief Emitted when the list of recent emoticons changes
     */
    void recentEmoticonsChanged();
    /*!
     * \brief Emitted when the emoji tone changes
     */
    void emojiToneChanged();

protected:
    /*!
     * \brief Determines whether the row at source_row should be included in the model
     * \param source_row The row number in the source model
     * \param source_parent The parent index in the source model
     * \return true if the row should be included, false otherwise
     */
    [[nodiscard]] bool filterAcceptsRow(int source_row, const QModelIndex &source_parent) const override;
    /*!
     * \brief Compares two emoticons for sorting
     * \param left The left emoticon index
     * \param right The right emoticon index
     * \return true if left should be sorted before right
     */
    [[nodiscard]] bool lessThan(const QModelIndex &left, const QModelIndex &right) const override;

private:
    class EmojiProxyModelPrivate;
    std::unique_ptr<EmojiProxyModelPrivate> const d;
};
}
