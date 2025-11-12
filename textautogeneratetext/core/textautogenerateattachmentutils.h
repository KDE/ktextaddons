/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QByteArray>
#include <QDebug>
#include <TextAutoGenerateText/TextAutoGenerateAttachment>
namespace TextAutoGenerateText
{
class TextAutoGenerateAttachments;
namespace TextAutoGenerateAttachmentUtils
{
struct TEXTAUTOGENERATETEXT_EXPORT AttachmentElementInfo {
    QByteArray mimeType;
    QByteArray content;
    QString name;
    TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType attachmentType = TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Unknown;
    [[nodiscard]] bool isValid() const;
};

[[nodiscard]] QByteArray extractContentFromFile(const QString &fileName);
[[nodiscard]] QByteArray generateUniqueId(const QByteArray &messageId, int index);
[[nodiscard]] TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType generateAttachmentType(const QByteArray &mimetype);

[[nodiscard]] TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateText::TextAutoGenerateAttachmentUtils::AttachmentElementInfo
createAttachmentElementInfoFromFile(const QString &fileName);

[[nodiscard]] TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateText::TextAutoGenerateAttachment
generateAttachmentFromAttachmentElementInfo(const TextAutoGenerateText::TextAutoGenerateAttachmentUtils::AttachmentElementInfo &info);

[[nodiscard]] QList<TextAutoGenerateAttachment>
generateAttachmentFromAttachmentElementInfos(const QList<TextAutoGenerateText::TextAutoGenerateAttachmentUtils::AttachmentElementInfo> &info);

[[nodiscard]] TextAutoGenerateAttachments *createTextAutoGenerateAttachments(const QList<TextAutoGenerateAttachment> &atts);
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateAttachmentUtils::AttachmentElementInfo &t);
