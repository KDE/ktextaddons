/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textemoticonscore_export.h"
#include <QIcon>
namespace TextEmoticonsCore
{
/**
 * @brief The CustomEmojiIconManager class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSCORE_EXPORT CustomEmojiIconManager
{
    Q_GADGET
public:
    CustomEmojiIconManager();
    virtual ~CustomEmojiIconManager();
    virtual QIcon generateIcon(const QString &customIdentifier);
};
}
