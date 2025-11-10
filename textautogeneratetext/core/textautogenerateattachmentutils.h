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
namespace TextAutoGenerateAttachmentUtils
{
struct TEXTAUTOGENERATETEXT_EXPORT AttachmentElementInfo {
    QByteArray mimeType;
    QByteArray content;
};

[[nodiscard]] QByteArray generateBase64(const QString &fileName);
[[nodiscard]] QByteArray generateUniqueId(const QByteArray &messageId, int index);
[[nodiscard]] TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType generateAttachmentType(const QByteArray &mimetype);

[[nodiscard]] TextAutoGenerateText::TextAutoGenerateAttachmentUtils::AttachmentElementInfo createAttachmentElementInfoFromFile(const QString &fileName);
};
}
TEXTAUTOGENERATETEXT_EXPORT QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateAttachmentUtils::AttachmentElementInfo &t);
