/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QObject>
class QDebug;
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateSearchMessage
 * \brief The TextAutoGenerateSearchMessage class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateSearchMessage
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateSearchMessage
{
public:
    /*!
     * Constructs a new TextAutoGenerateSearchMessage object.
     */
    TextAutoGenerateSearchMessage();
    /*!
     * Destroys the TextAutoGenerateSearchMessage object.
     */
    ~TextAutoGenerateSearchMessage();
    /*!
     * Returns the chat identifier.
     * \return The chat ID
     */
    [[nodiscard]] QByteArray chatId() const;
    /*!
     * Sets the chat identifier.
     * \param newChatId The chat ID to set
     */
    void setChatId(const QByteArray &newChatId);

    /*!
     * Returns the message identifier.
     * \return The message ID
     */
    [[nodiscard]] QByteArray messageId() const;
    /*!
     * Sets the message identifier.
     * \param newMessageId The message ID to set
     */
    void setMessageId(const QByteArray &newMessageId);

    /*!
     * Returns the preview text of the message.
     * \return The preview text
     */
    [[nodiscard]] QString previewText() const;
    /*!
     * Sets the preview text of the message.
     * \param newPreviewText The preview text to set
     */
    void setPreviewText(const QString &newPreviewText);

    /*!
     * Returns the creation date and time of the message.
     * \return The date/time as milliseconds since epoch
     */
    [[nodiscard]] qint64 dateTime() const;
    /*!
     * Sets the creation date and time of the message.
     * \param newDateTime The date/time as milliseconds since epoch
     */
    void setDateTime(qint64 newDateTime);

    /*!
     * Compares this search message with another for equality.
     * \param other The search message to compare with
     * \return true if equal, false otherwise
     */
    [[nodiscard]] bool operator==(const TextAutoGenerateSearchMessage &other) const;

private:
    QString mPreviewText;
    QByteArray mChatId;
    QByteArray mMessageId;
    qint64 mDateTime = -1;
};
}
Q_DECLARE_TYPEINFO(TextAutoGenerateText::TextAutoGenerateSearchMessage, Q_RELOCATABLE_TYPE);
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateSearchMessage &t);
