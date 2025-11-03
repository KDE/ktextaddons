/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateattachments.h"
#include "textautogeneratetextcore_memory_debug.h"
#include <QJsonArray>
#include <QJsonObject>

using namespace TextAutoGenerateText;
TextAutoGenerateAttachments::TextAutoGenerateAttachments()
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_MEMORY_LOG) << " TextAutoGenerateAttachments created " << this;
}

TextAutoGenerateAttachments::~TextAutoGenerateAttachments()
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_MEMORY_LOG) << " TextAutoGenerateAttachments deleted " << this;
}

TextAutoGenerateAttachments::TextAutoGenerateAttachments(const TextAutoGenerateAttachments &other)
    : QSharedData(other)
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_MEMORY_LOG) << " TextAutoGenerateAttachments created " << this;
}

bool TextAutoGenerateAttachments::isEmpty() const
{
    return mMessageAttachments.isEmpty();
}

QList<TextAutoGenerateAttachment> TextAutoGenerateAttachments::messageAttachments() const
{
    return mMessageAttachments;
}

void TextAutoGenerateAttachments::setMessageAttachments(const QList<TextAutoGenerateAttachment> &newMessageAttachments)
{
    mMessageAttachments = newMessageAttachments;
}

void TextAutoGenerateAttachments::parseMessageAttachments(const QJsonArray &attachments, const QByteArray &messageId)
{
    // TODO
}

bool TextAutoGenerateAttachments::operator==(const TextAutoGenerateAttachments &other) const
{
    return mMessageAttachments == other.messageAttachments();
}

QJsonArray TextAutoGenerateAttachments::serialize(const TextAutoGenerateAttachments &attachments)
{
    // TODO
    return {};
}

TextAutoGenerateAttachments *TextAutoGenerateAttachments::deserialize(const QJsonArray &o, const QByteArray &messageId)
{
    // TODO
    return {};
}
