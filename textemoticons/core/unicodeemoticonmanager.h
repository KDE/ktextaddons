/*
SPDX-FileCopyrightText: 2020-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "emoticoncategory.h"
#include "textemoticonscore_export.h"
#include "unicodeemoticon.h"
#include <QObject>

class UnicodeEmoticonManagerTest;

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

    Q_PROPERTY(QList<EmoticonCategory> categories READ categories CONSTANT)

public:
    static UnicodeEmoticonManager *self();

    [[nodiscard]] QList<UnicodeEmoticon> unicodeEmojiList() const;

    [[nodiscard]] QList<UnicodeEmoticon> emojisForCategory(const QString &category) const;
    [[nodiscard]] QList<EmoticonCategory> categories() const;
    [[nodiscard]] UnicodeEmoticon unicodeEmoticonForEmoji(const QString &emojiIdentifier) const;
    [[nodiscard]] int count() const;

    void loadUnicodeEmoji(const QString &filename);
    explicit UnicodeEmoticonManager(const QString &filename, QObject *parent = nullptr);

protected:
    explicit UnicodeEmoticonManager(QObject *parent = nullptr);
    ~UnicodeEmoticonManager() override;

    friend UnicodeEmoticonManagerTest;

private:
    std::unique_ptr<UnicodeEmoticonManagerPrivate> const d;
};
}
