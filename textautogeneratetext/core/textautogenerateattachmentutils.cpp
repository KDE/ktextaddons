/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogenerateattachmentutils.h"
#include "core/textautogenerateattachments.h"
#include "textautogeneratetextcore_debug.h"
#include <QFile>
#include <QFileInfo>
#include <QMimeDatabase>
#include <QString>
using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
QByteArray TextAutoGenerateAttachmentUtils::generateBase64(const QString &fileName)
{
    if (fileName.isEmpty()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "FileName is empty. It's a bug";
        return {};
    }

    QFile f(fileName);
    if (!f.open(QIODevice::WriteOnly)) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Impossible to open file:" << fileName;
        return {};
    }
    const QByteArray ba = f.readAll();

    // return u"data:image/%1;base64,%2"_s.arg(u"PNG"_s, QString::fromLatin1(ba.toBase64()));

    // TODO add info
    return ba;
}

QByteArray TextAutoGenerateAttachmentUtils::generateUniqueId(const QByteArray &messageId, int index)
{
    return messageId + QByteArray("_") + QByteArray::number(index);
}

TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType TextAutoGenerateAttachmentUtils::generateAttachmentType(const QByteArray &mimetype)
{
    if (mimetype.isEmpty()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "mimetype is empty. It's a bug";
        return TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Unknown;
    } else if (mimetype.startsWith("image/"_ba)) {
        return TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Image;
    } else if (mimetype.startsWith("video/"_ba)) {
        return TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Video;
    } else if (mimetype.startsWith("audio/"_ba)) {
        return TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Audio;
    } else {
        return TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::File;
    }
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateAttachmentUtils::AttachmentElementInfo &t)
{
    d.space() << "mimeType:" << t.mimeType;
    d.space() << "content:" << t.content;
    d.space() << "attachmentType:" << t.attachmentType;
    return d;
}

TextAutoGenerateAttachmentUtils::AttachmentElementInfo TextAutoGenerateAttachmentUtils::createAttachmentElementInfoFromFile(const QString &fileName)
{
    TextAutoGenerateAttachmentUtils::AttachmentElementInfo info;
    if (fileName.isEmpty()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Filename is empty. It's a bug";
        return info;
    }
    const QFileInfo fileInfo(fileName);
    const QMimeDatabase db;
    const QMimeType mimeType = db.mimeTypeForFile(fileInfo);
    info.mimeType = mimeType.name().toLatin1();
    info.content = generateBase64(fileName);
    info.attachmentType = generateAttachmentType(info.mimeType);
    return info;
}

bool TextAutoGenerateAttachmentUtils::AttachmentElementInfo::isValid() const
{
    return attachmentType != TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Unknown;
}

TextAutoGenerateAttachment TextAutoGenerateAttachmentUtils::generateAttachmentFromAttachmentElementInfo(const AttachmentElementInfo &info)
{
    TextAutoGenerateAttachment att;
    if (!info.isValid()) {
        return att;
    }
    att.setAttachmentType(info.attachmentType);
    att.setMimeType(info.mimeType);
    // TODO att.setName(info.name);
    att.setBase64(info.content);
    // TODO fix image ? not base64
    return att;
}

QList<TextAutoGenerateAttachment> TextAutoGenerateAttachmentUtils::generateAttachmentFromAttachmentElementInfos(const QList<AttachmentElementInfo> &info)
{
    QList<TextAutoGenerateAttachment> lstAttachment;
    for (const auto &attachmentInfo : info) {
        const TextAutoGenerateAttachment att = generateAttachmentFromAttachmentElementInfo(attachmentInfo);
        lstAttachment.append(att);
    }
    return lstAttachment;
}

TextAutoGenerateAttachments *TextAutoGenerateAttachmentUtils::createTextAutoGenerateAttachments(const QList<TextAutoGenerateAttachment> &atts)
{
    TextAutoGenerateAttachments *t = new TextAutoGenerateAttachments();
    t->setMessageAttachments(atts);
    return t;
}
