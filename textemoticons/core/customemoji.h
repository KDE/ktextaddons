/*
   SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textemoticonscore_export.h"
#include <QDebug>
#include <QString>
namespace TextEmoticonsCore
{
/**
 * @brief The CustomEmoji class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSCORE_EXPORT CustomEmoji
{
    Q_GADGET
public:
    CustomEmoji();

    [[nodiscard]] QString identifier() const;
    void setIdentifier(const QString &newIdentifier);

    [[nodiscard]] QString category() const;

    [[nodiscard]] bool isAnimatedEmoji() const;
    void setIsAnimatedEmoji(bool newIsAnimatedEmoji);

    [[nodiscard]] QString fileName() const;
    void setFileName(const QString &newFileName);

private:
    QString mIdentifier;
    QString mFileName;
    bool mIsAnimatedEmoji = false;
};
}
Q_DECLARE_METATYPE(TextEmoticonsCore::CustomEmoji)
Q_DECLARE_TYPEINFO(TextEmoticonsCore::CustomEmoji, Q_MOVABLE_TYPE);
TEXTEMOTICONSCORE_EXPORT QDebug operator<<(QDebug d, const TextEmoticonsCore::CustomEmoji &t);
