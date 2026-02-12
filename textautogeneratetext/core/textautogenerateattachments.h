/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QList>
#include <QSharedData>
#include <TextAutoGenerateText/TextAutoGenerateAttachment>
class QDebug;
namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateAttachments
 * \brief The TextAutoGenerateAttachments class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateAttachments
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateAttachments : public QSharedData
{
public:
    /*!
     * Constructs a new TextAutoGenerateAttachments object.
     */
    TextAutoGenerateAttachments();
    /*!
     * Destroys the TextAutoGenerateAttachments object.
     */
    ~TextAutoGenerateAttachments();
    /*!
     * Constructs a copy of the TextAutoGenerateAttachments object from another object.
     * \param other The TextAutoGenerateAttachments object to copy from
     */
    explicit TextAutoGenerateAttachments(const TextAutoGenerateAttachments &other);

    /*!
     * Returns whether the attachments collection is empty.
     * \return true if there are no attachments, false otherwise
     */
    [[nodiscard]] bool isEmpty() const;

    /*!
     * Returns the list of message attachments.
     * \return A list of TextAutoGenerateAttachment objects
     */
    [[nodiscard]] QList<TextAutoGenerateAttachment> messageAttachments() const;
    /*!
     * Sets the list of message attachments.
     * \param newMessageAttachments The attachments to set
     */
    void setMessageAttachments(const QList<TextAutoGenerateAttachment> &newMessageAttachments);

    /*!
     * Compares this TextAutoGenerateAttachments with another for equality.
     * \param other The TextAutoGenerateAttachments to compare with
     * \return true if both objects are equal, false otherwise
     */
    [[nodiscard]] bool operator==(const TextAutoGenerateAttachments &other) const;

    /*!
     * Serializes the given TextAutoGenerateAttachments object.
     * \param attachments The TextAutoGenerateAttachments to serialize
     * \return The serialized data as a QJsonArray
     */
    [[nodiscard]] static QJsonArray serialize(const TextAutoGenerateAttachments &attachments);
    /*!
     * Deserializes a TextAutoGenerateAttachments object from JSON.
     * \param o The JSON array to deserialize from
     * \param messageId The message ID for context
     * \return A pointer to the deserialized TextAutoGenerateAttachments
     */
    [[nodiscard]] static TextAutoGenerateAttachments *deserialize(const QJsonArray &o, const QByteArray &messageId);

private:
    QList<TextAutoGenerateAttachment> mMessageAttachments;
};
}

TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateAttachments &t);
