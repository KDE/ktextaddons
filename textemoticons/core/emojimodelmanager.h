/*
   SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>

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
public:
    explicit EmojiModelManager(QObject *parent = nullptr);
    ~EmojiModelManager() override;

    static EmojiModelManager *self();
    [[nodiscard]] TextEmoticonsCore::EmojiModel *emojiModel() const;

    [[nodiscard]] const QStringList &recentIdentifier() const;
    void setRecentIdentifier(const QStringList &newRecentIdentifier);
    void addIdentifier(const QString &identifier);

    [[nodiscard]] TextEmoticonsCore::CustomEmojiIconManager *customEmojiIconManager() const;
    void setCustomEmojiIconManager(TextEmoticonsCore::CustomEmojiIconManager *newCustomEmojiIconManager);

    [[nodiscard]] QStringList excludeEmoticons() const;
    void setExcludeEmoticons(const QStringList &emoticons);

Q_SIGNALS:
    void usedIdentifierChanged(const QStringList &lst);
    void excludeEmoticonsChanged();

private:
    class EmojiModelManagerPrivate;
    std::unique_ptr<EmojiModelManagerPrivate> const d;
};
}
