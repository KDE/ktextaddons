/*
   SPDX-FileCopyrightText: 2021-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textemoticonscore_export.h"
#include <QAbstractListModel>
#include <TextEmoticonsCore/CustomEmoji>
#include <TextEmoticonsCore/UnicodeEmoticon>
namespace TextEmoticonsCore
{
class CustomEmojiIconManager;
/*!
 * \class TextEmoticonsCore::EmojiModel
 * \inmodule TextEmoticonsCore
 * \inheaderfile TextEmoticonsCore/EmojiModel
 *
 * \brief The EmojiModel class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSCORE_EXPORT EmojiModel : public QAbstractListModel
{
    Q_OBJECT
public:
    enum EmoticonsRoles {
        UnicodeEmoji = Qt::UserRole + 1,
        Identifier,
        Category,
        Order,
        Animated,
        AnimatedFileName,
        IsCustom,
        FileName,
        DiversityChildren,
    };
    Q_ENUM(EmoticonsRoles)

    /*!
     * \brief Constructor for EmojiModel
     * \param parent The parent object
     */
    explicit EmojiModel(QObject *parent = nullptr);
    /*!
     * \brief Destructor for EmojiModel
     */
    ~EmojiModel() override;

    /*!
     * \brief Returns the number of rows in the model
     * \param parent The parent model index
     * \return The row count
     */
    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    /*!
     * \brief Returns the data for a given index and role
     * \param index The model index
     * \param role The data role
     * \return The data as a QVariant
     */
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    /*!
     * \brief Returns the list of unicode emoticons
     * \return A reference to the emoticon list
     */
    [[nodiscard]] const QList<TextEmoticonsCore::UnicodeEmoticon> &emoticonList() const;
    /*!
     * \brief Sets the list of unicode emoticons
     * \param newEmoticonList The emoticon list to set
     */
    void setUnicodeEmoticonList(const QList<TextEmoticonsCore::UnicodeEmoticon> &newEmoticonList);

    /*!
     * \brief Returns the list of custom emojis
     * \return The custom emoji list
     */
    [[nodiscard]] QList<TextEmoticonsCore::CustomEmoji> customEmojiList() const;
    /*!
     * \brief Sets the list of custom emojis
     * \param newCustomEmojiList The custom emoji list to set
     */
    void setCustomEmojiList(const QList<TextEmoticonsCore::CustomEmoji> &newCustomEmojiList);

    /*!
     * \brief Returns the custom emoji icon manager
     * \return Pointer to the CustomEmojiIconManager
     */
    [[nodiscard]] TextEmoticonsCore::CustomEmojiIconManager *customEmojiIconManager() const;
    /*!
     * \brief Sets the custom emoji icon manager
     * \param newCustomEmojiIconManager The icon manager to set
     */
    void setCustomEmojiIconManager(TextEmoticonsCore::CustomEmojiIconManager *newCustomEmojiIconManager);

    /*!
     * \brief Sets emoticons to exclude from the model
     * \param emoticons The list of emoticons to exclude
     */
    void setExcludeEmoticons(const QStringList &emoticons);

    /*!
     * \brief Returns the role names for the model
     * \return A hash of role numbers to role names
     */
    QHash<int, QByteArray> roleNames() const override;

private:
    Q_DISABLE_COPY(EmojiModel)
    QList<TextEmoticonsCore::UnicodeEmoticon> mEmoticonList;
    QList<TextEmoticonsCore::CustomEmoji> mCustomEmojiList;
    TextEmoticonsCore::CustomEmojiIconManager *mCustomEmojiIconManager = nullptr;
};
}
