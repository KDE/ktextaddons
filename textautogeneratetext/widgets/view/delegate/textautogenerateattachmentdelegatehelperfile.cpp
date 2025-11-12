/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogenerateattachmentdelegatehelperfile.h"
#include "core/models/textautogeneratemessagesmodel.h"

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateAttachmentDelegateHelperFile::TextAutoGenerateAttachmentDelegateHelperFile(QObject *parent)
    : TextAutoGenerateAttachmentDelegateHelperBase{parent}
{
}

TextAutoGenerateAttachmentDelegateHelperFile::~TextAutoGenerateAttachmentDelegateHelperFile() = default;

// Icon + text
void TextAutoGenerateAttachmentDelegateHelperFile::draw(const TextAutoGenerateText::TextAutoGenerateAttachment &msgAttach,
                                                        QPainter *painter,
                                                        QRect attachmentsRect,
                                                        const QModelIndex &index,
                                                        const QStyleOptionViewItem &option) const
{
    const FileLayout layout = doLayout(msgAttach, option, attachmentsRect.width());
    // TODO add msgAttach.mimeType()

    qDebug() << " extAutoGenerateAttachmentDelegateHelperFile::draw";
    // TODO
}

QSize TextAutoGenerateAttachmentDelegateHelperFile::sizeHint(const TextAutoGenerateText::TextAutoGenerateAttachment &msgAttach,
                                                             const QModelIndex &index,
                                                             int maxWidth,
                                                             const QStyleOptionViewItem &option) const
{
    const FileLayout layout = doLayout(msgAttach, option, maxWidth);
    // TODO
    return QSize(50, 50);
}

TextAutoGenerateAttachmentDelegateHelperFile::FileLayout
TextAutoGenerateAttachmentDelegateHelperFile::doLayout(const TextAutoGenerateText::TextAutoGenerateAttachment &msgAttach,
                                                       const QStyleOptionViewItem &option,
                                                       int attachmentsWidth) const
{
    FileLayout layout;
    // TODO
    return layout;
}

#include "moc_textautogenerateattachmentdelegatehelperfile.cpp"
