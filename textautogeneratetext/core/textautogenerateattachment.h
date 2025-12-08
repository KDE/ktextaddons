/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QMetaType>
#include <QSharedData>

namespace TextAutoGenerateText
{
/**
 * @brief The TextAutoGenerateMessage class
 * @author Laurent Montel <montel@kde.org>
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

    TextAutoGenerateAttachment();
    ~TextAutoGenerateAttachment();

    [[nodiscard]] QByteArray content() const;
    void setContent(const QByteArray &b);

    [[nodiscard]] bool operator==(const TextAutoGenerateAttachment &other) const;

    [[nodiscard]] bool isValid() const;

    [[nodiscard]] AttachmentType attachmentType() const;
    void setAttachmentType(AttachmentType newAttachmentType);

    [[nodiscard]] static QJsonObject serialize(const TextAutoGenerateAttachment &attachment);
    [[nodiscard]] static TextAutoGenerateAttachment deserialize(const QJsonObject &o);

    [[nodiscard]] QByteArray mimeType() const;
    void setMimeType(const QByteArray &newMimeType);

    [[nodiscard]] QString name() const;
    void setName(const QString &newName);

    [[nodiscard]] bool showAttachment() const;
    void setShowAttachment(bool newShowAttachment);

private:
    AttachmentType mAttachmentType = AttachmentType::Unknown;
    QByteArray mContent;
    QByteArray mMimeType;
    QString mName;
    bool mShowAttachment = true;
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateAttachment &t);
