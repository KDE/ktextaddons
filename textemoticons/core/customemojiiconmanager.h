/*
   SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once
#include "textemoticonscore_export.h"
#include <QIcon>
#include <QObject>
namespace TextEmoticonsCore
{
/*!
 * \class TextEmoticonsCore::CustomEmojiIconManager
 * \inmodule TextEmoticonsCore
 * \inheaderfile TextEmoticonsCore/CustomEmojiIconManager
 *
 * \brief The CustomEmojiIconManager class
 * \author Laurent Montel <montel@kde.org>
 */
class TEXTEMOTICONSCORE_EXPORT CustomEmojiIconManager : public QObject
{
    Q_OBJECT
public:
    /*!
     */
    explicit CustomEmojiIconManager(QObject *parent = nullptr);
    /*!
     */
    ~CustomEmojiIconManager() override;
    /*!
     */
    virtual QIcon generateIcon(const QString &customIdentifier);
    /*!
     */
    virtual QString fileName(const QString &customIdentifier);
};
}
