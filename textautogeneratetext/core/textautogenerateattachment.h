/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QMetaType>
#include <QSharedData>

namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateAttachment
 * \brief The TextAutoGenerateAttachment class
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateAttachment
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateAttachment
{
    Q_GADGET
public:
    enum class AttachmentType : uint8_t {
        Unknown = 0,
        File,
        Image,
        Audio,
        Video,
    };
    Q_ENUM(AttachmentType)

    /*!
     * Constructs a new TextAutoGenerateAttachment object.
     */
    TextAutoGenerateAttachment();
    /*!
     * Destroys the TextAutoGenerateAttachment object.
     */
    ~TextAutoGenerateAttachment();

    /*!
     * Returns the content of the attachment.
     * \return The attachment content as a QByteArray
     */
    [[nodiscard]] QByteArray content() const;
    /*!
     * Sets the content of the attachment.
     * \param b The content to set
     */
    void setContent(const QByteArray &b);

    /*!
     * Compares this TextAutoGenerateAttachment with another for equality.
     * \param other The TextAutoGenerateAttachment to compare with
     * \return true if both attachments are equal, false otherwise
     */
    [[nodiscard]] bool operator==(const TextAutoGenerateAttachment &other) const;

    /*!
     * Returns whether the attachment is valid.
     * \return true if the attachment is valid, false otherwise
     */
    [[nodiscard]] bool isValid() const;

    /*!
     * Returns the type of the attachment.
     * \return The AttachmentType enum value
     */
    [[nodiscard]] AttachmentType attachmentType() const;
    /*!
     * Sets the type of the attachment.
     * \param newAttachmentType The attachment type to set
     */
    void setAttachmentType(AttachmentType newAttachmentType);

    /*!
     * Serializes the given TextAutoGenerateAttachment object.
     * \param attachment The TextAutoGenerateAttachment to serialize
     * \return The serialized data as a QJsonObject
     */
    [[nodiscard]] static QJsonObject serialize(const TextAutoGenerateAttachment &attachment);
    /*!
     * Deserializes a TextAutoGenerateAttachment object from JSON.
     * \param o The JSON object to deserialize from
     * \return The deserialized TextAutoGenerateAttachment
     */
    [[nodiscard]] static TextAutoGenerateAttachment deserialize(const QJsonObject &o);

    /*!
     * Returns the MIME type of the attachment.
     * \return The MIME type as a QByteArray
     */
    [[nodiscard]] QByteArray mimeType() const;
    /*!
     * Sets the MIME type of the attachment.
     * \param newMimeType The MIME type to set
     */
    void setMimeType(const QByteArray &newMimeType);

    /*!
     * Returns the name of the attachment.
     * \return The attachment name as a QString
     */
    [[nodiscard]] QString name() const;
    /*!
     * Sets the name of the attachment.
     * \param newName The name to set
     */
    void setName(const QString &newName);

    /*!
     * Returns whether the attachment should be shown.
     * \return true if the attachment should be shown, false otherwise
     */
    [[nodiscard]] bool showAttachment() const;
    /*!
     * Sets whether the attachment should be shown.
     * \param newShowAttachment true to show the attachment, false to hide
     */
    void setShowAttachment(bool newShowAttachment);

    /*!
     * Returns the unique identifier of the attachment.
     * \return The attachment ID as a QByteArray
     */
    [[nodiscard]] QByteArray attachmentId() const;
    /*!
     * Sets the unique identifier of the attachment.
     * \param newAttachmentId The ID to set
     */
    void setAttachmentId(const QByteArray &newAttachmentId);

private:
    AttachmentType mAttachmentType = AttachmentType::Unknown;
    QByteArray mContent;
    QByteArray mMimeType;
    QByteArray mAttachmentId;
    QString mName;
    bool mShowAttachment = true;
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateAttachment &t);
