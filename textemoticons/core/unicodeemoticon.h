/*
   SPDX-FileCopyrightText: 2018-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textemoticonscore_export.h"
#include <QDebug>
#include <QString>
namespace TextEmoticonsCore
{
/**
 * @brief The UnicodeEmoticon class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSCORE_EXPORT UnicodeEmoticon
{
    Q_GADGET
public:
    UnicodeEmoticon();

    [[nodiscard]] QString identifier() const;
    void setIdentifier(const QString &identifier);

    [[nodiscard]] QString name() const;
    void setName(const QString &name);

    [[nodiscard]] QString unicode() const;
    [[nodiscard]] QString unicodeDisplay() const;
    void setUnicode(const QString &unicode);

    [[nodiscard]] QString category() const;
    void setCategory(const QString &category);

    [[nodiscard]] QStringList aliases() const;
    void setAliases(const QStringList &aliases);

    [[nodiscard]] bool hasEmoji(const QString &identifier) const;

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] int order() const;
    void setOrder(int order);

    [[nodiscard]] QString key() const;
    void setKey(const QString &key);

    [[nodiscard]] bool operator==(const UnicodeEmoticon &other) const;

    void setDiversityChildren(bool b);
    [[nodiscard]] bool diversityChildren() const;

private:
    QStringList mAliases;
    QString mIdentifier;
    QString mUnicode;
    QString mCategory;
    QString mKey;
    QString mName;
    mutable QString mCachedHtml;
    int mOrder = -1;
    bool mHasDiversityChildren = false;
};
}
Q_DECLARE_METATYPE(TextEmoticonsCore::UnicodeEmoticon)
Q_DECLARE_TYPEINFO(TextEmoticonsCore::UnicodeEmoticon, Q_MOVABLE_TYPE);
TEXTEMOTICONSCORE_EXPORT QDebug operator<<(QDebug d, const TextEmoticonsCore::UnicodeEmoticon &t);
