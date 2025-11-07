/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QByteArray>
#include <TextAutoGenerateText/TextAutoGenerateAttachment>
namespace TextAutoGenerateText
{
namespace TextAutoGenerateAttachmentUtils
{
[[nodiscard]] QByteArray generateBase64(const QString &fileName);
[[nodiscard]] QByteArray generateUniqueId(const QByteArray &messageId, int index);
[[nodiscard]] TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType generateAttachmentType(const QByteArray &mimetype);
};
}
