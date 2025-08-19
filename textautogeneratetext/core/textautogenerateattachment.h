/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QObject>
#include <QSharedData>

namespace TextAutoGenerateText
{
/**
 * @brief The TextAutoGenerateMessage class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateAttachment : public QSharedData
{
    Q_GADGET
public:
    enum class AttachmentType : uint8_t {
        Unknown,
        File,
        Image,
    };
    Q_ENUM(AttachmentType)

    TextAutoGenerateAttachment();
    ~TextAutoGenerateAttachment();
    explicit TextAutoGenerateAttachment(const TextAutoGenerateAttachment &other);

    [[nodiscard]] QByteArray image() const;
    void setImage(const QByteArray &newImage);

    [[nodiscard]] bool operator==(const TextAutoGenerateAttachment &other) const;

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] AttachmentType attachmentType() const;
    void setAttachmentType(const AttachmentType &newAttachmentType);

    static void serialize(const TextAutoGenerateAttachment &attachment, QJsonObject &o);
    static TextAutoGenerateAttachment *deserialize(const QJsonObject &o);

    [[nodiscard]] QByteArray mimeType() const;
    void setMimeType(const QByteArray &newMimeType);

private:
    AttachmentType mAttachmentType = AttachmentType::Unknown;
    QByteArray mImage;
    QByteArray mMimeType;
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateAttachment &t);
