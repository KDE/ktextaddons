/*
   SPDX-FileCopyrightText: 2019-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textemoticonscore_export.h"
#include "unicodeemoticon.h"
#include <QList>
namespace TextEmoticonsCore
{
/*!
 * \class TextEmoticonsCore::UnicodeEmoticonParser
 * \inmodule TextEmoticonsCore
 * \inheaderfile TextEmoticonsCore/UnicodeEmoticonParser
 *
 * \brief The UnicodeEmoticonParser class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSCORE_EXPORT UnicodeEmoticonParser
{
public:
    /*!
     * \brief Constructs a UnicodeEmoticonParser
     */
    UnicodeEmoticonParser();
    /*!
     * \brief Destroys the UnicodeEmoticonParser
     */
    ~UnicodeEmoticonParser() = default;

    /*!
     * \brief Parses emoticon data from a JSON object
     * \param o The JSON object containing emoticon data
     * \return A list of parsed UnicodeEmoticon objects
     */
    [[nodiscard]] QList<UnicodeEmoticon> parse(const QJsonObject &o) const;
    /*!
     * \brief Converts emoticon category name to sort order value
     * \param name The category name
     * \return The sort order value for the category
     */
    [[nodiscard]] static int changeOrder(const QString &name);
};
}
