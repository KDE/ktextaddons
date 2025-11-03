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
    QJsonArray array;
    for (const auto &att : attachments.messageAttachments()) {
        // TODO array.append(TextAutoGenerateAttachment::serialize(attachmentInfo));
    }
    return array;
}

TextAutoGenerateAttachments *TextAutoGenerateAttachments::deserialize(const QJsonArray &attachmentsArray, const QByteArray &messageId)
{
    QList<TextAutoGenerateAttachment> attachmentList;
    for (int i = 0; i < attachmentsArray.count(); ++i) {
        // TODO
        /*
        const QJsonObject attachment = attachmentsArray.at(i).toObject();
        TextAutoGenerateAttachment att = TextAutoGenerateAttachment::deserialize(attachment);
        // att.setAttachmentId(MessageUtils::generateUniqueId(messageId, i));
        if (att.isValid()) {
            attachmentInfo.append(std::move(att));
        }
        */
    }
    auto final = new TextAutoGenerateAttachments;
    final->setMessageAttachments(attachmentList);
    return final;
}

QDebug operator<<(QDebug d, const TextAutoGenerateAttachments &t)
{
    for (int i = 0; i < t.messageAttachments().count(); i++) {
        d.space() << t.messageAttachments().at(i) << "\n";
    }
    return d;
}
