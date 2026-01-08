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
     */
    UnicodeEmoticonParser();
    /*!
     */
    ~UnicodeEmoticonParser();

    /*!
     */
    [[nodiscard]] QList<UnicodeEmoticon> parse(const QJsonObject &o) const;
    /*!
     */
    [[nodiscard]] static int changeOrder(const QString &name);
};
}
