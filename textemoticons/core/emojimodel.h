/*
   SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>

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
/**
 * @brief The EmojiModel class
 * @author Laurent Montel <montel@kde.org>
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
    };
    Q_ENUM(EmoticonsRoles)

    explicit EmojiModel(QObject *parent = nullptr);
    ~EmojiModel() override;

    [[nodiscard]] int rowCount(const QModelIndex &parent = QModelIndex()) const override;
    [[nodiscard]] QVariant data(const QModelIndex &index, int role) const override;

    [[nodiscard]] const QList<TextEmoticonsCore::UnicodeEmoticon> &emoticonList() const;
    void setUnicodeEmoticonList(const QList<TextEmoticonsCore::UnicodeEmoticon> &newEmoticonList);

    [[nodiscard]] QList<TextEmoticonsCore::CustomEmoji> customEmojiList() const;
    void setCustomEmojiList(const QList<TextEmoticonsCore::CustomEmoji> &newCustomEmojiList);

    [[nodiscard]] TextEmoticonsCore::CustomEmojiIconManager *customEmojiIconManager() const;
    void setCustomEmojiIconManager(TextEmoticonsCore::CustomEmojiIconManager *newCustomEmojiIconManager);

    void setExcludeEmoticons(const QStringList &emoticons);

private:
    Q_DISABLE_COPY(EmojiModel)
    QList<TextEmoticonsCore::UnicodeEmoticon> mEmoticonList;
    QList<TextEmoticonsCore::CustomEmoji> mCustomEmojiList;
    TextEmoticonsCore::CustomEmojiIconManager *mCustomEmojiIconManager = nullptr;
};
}
