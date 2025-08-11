/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateattachment.h"
#include "textautogeneratetextcore_memory_debug.h"
using namespace TextAutoGenerateText;
TextAutoGenerateAttachment::TextAutoGenerateAttachment()
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_MEMORY_LOG) << " TextAutoGenerateAttachment created " << this;
}

TextAutoGenerateAttachment::~TextAutoGenerateAttachment()
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_MEMORY_LOG) << " TextAutoGenerateAttachment deleted " << this;
}

TextAutoGenerateAttachment::TextAutoGenerateAttachment(const TextAutoGenerateAttachment &other)
    : QSharedData(other)
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_MEMORY_LOG) << " TextAutoGenerateAnswerInfo created " << this;
    mImage = other.mImage;
}

QByteArray TextAutoGenerateAttachment::image() const
{
    return mImage;
}

void TextAutoGenerateAttachment::setImage(const QByteArray &newImage)
{
    mImage = newImage;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateAttachment &t)
{
    d.space() << "mImage:" << t.image();
    d.space() << "mAttachmentType:" << t.attachmentType();
    return d;
}

bool TextAutoGenerateAttachment::operator==(const TextAutoGenerateAttachment &other) const
{
    return mImage == other.mImage;
}

TextAutoGenerateAttachment::AttachmentType TextAutoGenerateAttachment::attachmentType() const
{
    return mAttachmentType;
}

void TextAutoGenerateAttachment::setAttachmentType(const AttachmentType &newAttachmentType)
{
    mAttachmentType = newAttachmentType;
}
