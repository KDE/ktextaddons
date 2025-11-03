/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateattachment.h"
#include "textautogeneratetextcore_memory_debug.h"
#include <QJsonObject>
using namespace Qt::Literals::StringLiterals;
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
    qCDebug(TEXTAUTOGENERATETEXT_CORE_MEMORY_LOG) << " TextAutoGenerateAttachment created " << this;
    mBase64 = other.mBase64;
    mAttachmentType = other.mAttachmentType;
    mMimeType = other.mMimeType;
    mName = other.mName;
}

QByteArray TextAutoGenerateAttachment::base64() const
{
    return mBase64;
}

void TextAutoGenerateAttachment::setBase64(const QByteArray &b)
{
    mBase64 = b;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateAttachment &t)
{
    d.space() << "mBase64:" << t.base64();
    d.space() << "mAttachmentType:" << t.attachmentType();
    d.space() << "mMimeType:" << t.mimeType();
    d.space() << "mName:" << t.name();
    return d;
}

bool TextAutoGenerateAttachment::operator==(const TextAutoGenerateAttachment &other) const
{
    return (mBase64 == other.mBase64) && (mAttachmentType == other.mAttachmentType) && (mMimeType == other.mMimeType) && (mName == other.mName);
}

bool TextAutoGenerateAttachment::isValid() const
{
    return (mAttachmentType != AttachmentType::Unknown) && !mBase64.isEmpty();
}

TextAutoGenerateAttachment::AttachmentType TextAutoGenerateAttachment::attachmentType() const
{
    return mAttachmentType;
}

void TextAutoGenerateAttachment::setAttachmentType(AttachmentType newAttachmentType)
{
    mAttachmentType = newAttachmentType;
}

void TextAutoGenerateAttachment::serialize(const TextAutoGenerateAttachment &attachment, QJsonObject &o)
{
    o["type"_L1] = static_cast<int>(attachment.attachmentType());
    o["mimetype"_L1] = QString::fromLatin1(attachment.mimeType());
    o["base64"_L1] = QString::fromLatin1(attachment.base64());
    o["name"_L1] = attachment.name();
}

TextAutoGenerateAttachment *TextAutoGenerateAttachment::deserialize(const QJsonObject &o)
{
    TextAutoGenerateAttachment *att = new TextAutoGenerateAttachment;
    att->setAttachmentType(static_cast<TextAutoGenerateAttachment::AttachmentType>(o["type"_L1].toInt(static_cast<int>(AttachmentType::Unknown))));
    att->setMimeType(o["mimetype"_L1].toString().toLatin1());
    att->setBase64(o["base64"_L1].toString().toLatin1());
    att->setName(o["name"_L1].toString());
    return att;
}

QByteArray TextAutoGenerateAttachment::mimeType() const
{
    return mMimeType;
}

void TextAutoGenerateAttachment::setMimeType(const QByteArray &newMimeType)
{
    mMimeType = newMimeType;
}

QString TextAutoGenerateAttachment::name() const
{
    return mName;
}

void TextAutoGenerateAttachment::setName(const QString &newName)
{
    mName = newName;
}

#include "moc_textautogenerateattachment.cpp"
