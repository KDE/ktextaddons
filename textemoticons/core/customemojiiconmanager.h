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
     * \brief Constructor for CustomEmojiIconManager
     * \param parent The parent object
     */
    explicit CustomEmojiIconManager(QObject *parent = nullptr);
    /*!
     * \brief Destructor for CustomEmojiIconManager
     */
    ~CustomEmojiIconManager() override;
    /*!
     * \brief Generates an icon for a custom emoji
     * \param customIdentifier The identifier of the custom emoji
     * \return The generated QIcon
     */
    virtual QIcon generateIcon(const QString &customIdentifier);
    /*!
     * \brief Returns the file name for a custom emoji
     * \param customIdentifier The identifier of the custom emoji
     * \return The file name string
     */
    virtual QString fileName(const QString &customIdentifier);
};
}
