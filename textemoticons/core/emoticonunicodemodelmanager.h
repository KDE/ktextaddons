/*
   SPDX-FileCopyrightText: 2021-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include "textemoticonscore_export.h"
#include <QObject>
namespace TextEmoticonsCore
{
class EmojiModel;
class CustomEmojiIconManager;
// TODO rename as EmojiModelManager
class TEXTEMOTICONSCORE_EXPORT EmoticonUnicodeModelManager : public QObject
{
    Q_OBJECT
public:
    explicit EmoticonUnicodeModelManager(QObject *parent = nullptr);
    ~EmoticonUnicodeModelManager() override;

    static EmoticonUnicodeModelManager *self();
    Q_REQUIRED_RESULT TextEmoticonsCore::EmojiModel *emojiModel() const;

    Q_REQUIRED_RESULT const QStringList &recentIdentifier() const;
    void setRecentIdentifier(const QStringList &newRecentIdentifier);
    void addIdentifier(const QString &identifier);

    Q_REQUIRED_RESULT TextEmoticonsCore::CustomEmojiIconManager *customEmojiIconManager() const;
    void setCustomEmojiIconManager(TextEmoticonsCore::CustomEmojiIconManager *newCustomEmojiIconManager);

Q_SIGNALS:
    void usedIdentifierChanged(const QStringList &lst);

private:
    TextEmoticonsCore::EmojiModel *const mEmojiModel;
    QStringList mRecentIdentifier;
    void loadRecentUsed();
    void writeRecentUsed();
};
}
