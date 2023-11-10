/*
   SPDX-FileCopyrightText: 2020-2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "emoticoncategory.h"
#include "textemoticonscore_export.h"
#include "unicodeemoticon.h"
#include <QObject>
namespace TextEmoticonsCore
{
class UnicodeEmoticonManagerPrivate;
/**
 * @brief The UnicodeEmoticonManager class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSCORE_EXPORT UnicodeEmoticonManager : public QObject
{
    Q_OBJECT
public:
    explicit UnicodeEmoticonManager(QObject *parent = nullptr);
    ~UnicodeEmoticonManager() override;

    static UnicodeEmoticonManager *self();

    [[nodiscard]] QList<UnicodeEmoticon> unicodeEmojiList() const;

    [[nodiscard]] QList<UnicodeEmoticon> emojisForCategory(const QString &category) const;
    [[nodiscard]] QList<EmoticonCategory> categories() const;
    [[nodiscard]] UnicodeEmoticon unicodeEmoticonForEmoji(const QString &emojiIdentifier) const;
    [[nodiscard]] int count() const;

private:
    std::unique_ptr<UnicodeEmoticonManagerPrivate> const d;
};
}
