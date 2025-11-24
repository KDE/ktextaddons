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
QByteArray TextAutoGenerateAttachmentUtils::extractContentFromFile(const QString &fileName)
{
    if (fileName.isEmpty()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "FileName is empty. It's a bug";
        return {};
    }

    QFile f(fileName);
    if (!f.open(QIODevice::ReadOnly)) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Impossible to open file:" << fileName;
        return {};
    }
    const QByteArray ba = f.readAll();

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
    d.space() << "name:" << t.name;
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
    info.attachmentType = generateAttachmentType(info.mimeType);
    info.name = fileInfo.fileName();
    const QByteArray ba = extractContentFromFile(fileName);
    if (info.attachmentType == TextAutoGenerateText::TextAutoGenerateAttachment::AttachmentType::Image) {
        // Convert to png ?
        info.content = "data:"_ba + info.mimeType + ";base64,"_ba + ba.toBase64();
    } else {
        info.content = ba;
    }
    return info;
}

QList<TextAutoGenerateText::TextAutoGenerateAttachmentUtils::AttachmentElementInfo>
TextAutoGenerateAttachmentUtils::createAttachmentElementInfoFromFileList(const QStringList &files)
{
    QList<TextAutoGenerateText::TextAutoGenerateAttachmentUtils::AttachmentElementInfo> infos;
    for (const auto &file : files) {
        const auto info = createAttachmentElementInfoFromFile(file);
        if (info.isValid()) {
            infos.append(info);
        }
    }
    return infos;
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
    att.setName(info.name);
    att.setContent(info.content);
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
