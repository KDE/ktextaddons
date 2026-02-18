/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textemoticonscore_export.h"
#include <QMetaType>
#include <QString>
class QDebug;
namespace TextEmoticonsCore
{
/*!
 * \class TextEmoticonsCore::CustomEmoji
 * \inmodule TextEmoticonsCore
 * \inheaderfile TextEmoticonsCore/CustomEmoji
 *
 * \brief The CustomEmoji class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSCORE_EXPORT CustomEmoji
{
    Q_GADGET
public:
    /*!
     * \brief Constructor for CustomEmoji
     */
    CustomEmoji();

    /*!
     * \brief Returns the identifier of the custom emoji
     * \return The emoji identifier string
     */
    [[nodiscard]] QString identifier() const;
    /*!
     * \brief Sets the identifier of the custom emoji
     * \param newIdentifier The emoji identifier to set
     */
    void setIdentifier(const QString &newIdentifier);

    /*!
     * \brief Returns the category of the custom emoji
     * \return The category string
     */
    [[nodiscard]] QString category() const;

    /*!
     * \brief Checks if the emoji is animated
     * \return True if the emoji is animated, false otherwise
     */
    [[nodiscard]] bool isAnimatedEmoji() const;
    /*!
     * \brief Sets whether the emoji is animated
     * \param newIsAnimatedEmoji True to mark as animated, false otherwise
     */
    void setIsAnimatedEmoji(bool newIsAnimatedEmoji);

    /*!
     * \brief Returns the file name of the emoji
     * \return The file name string
     */
    [[nodiscard]] QString fileName() const;
    /*!
     * \brief Sets the file name of the emoji
     * \param newFileName The file name to set
     */
    void setFileName(const QString &newFileName);

private:
    QString mIdentifier;
    QString mFileName;
    bool mIsAnimatedEmoji = false;
};
}
Q_DECLARE_METATYPE(TextEmoticonsCore::CustomEmoji)
Q_DECLARE_TYPEINFO(TextEmoticonsCore::CustomEmoji, Q_MOVABLE_TYPE);
/*!
 */
TEXTEMOTICONSCORE_EXPORT QDebug operator<<(QDebug d, const TextEmoticonsCore::CustomEmoji &t);
