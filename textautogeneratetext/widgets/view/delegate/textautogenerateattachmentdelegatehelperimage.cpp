/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogenerateattachmentdelegatehelperimage.h"
#include <QDebug>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateAttachmentDelegateHelperImage::TextAutoGenerateAttachmentDelegateHelperImage(QObject *parent)
    : TextAutoGenerateAttachmentDelegateHelperBase{parent}
{
}

TextAutoGenerateAttachmentDelegateHelperImage::~TextAutoGenerateAttachmentDelegateHelperImage() = default;

void TextAutoGenerateAttachmentDelegateHelperImage::draw(const TextAutoGenerateText::TextAutoGenerateAttachment &msgAttach,
                                                         QPainter *painter,
                                                         QRect attachmentsRect,
                                                         const QModelIndex &index,
                                                         const QStyleOptionViewItem &option) const
{
    const ImageLayout layout = layoutImage(msgAttach, option, attachmentsRect.width(), attachmentsRect.height());

    // TODO
    qDebug() << " TextAutoGenerateAttachmentDelegateHelperImage::draw";
}

QSize TextAutoGenerateAttachmentDelegateHelperImage::sizeHint(const TextAutoGenerateText::TextAutoGenerateAttachment &msgAttach,
                                                              const QModelIndex &index,
                                                              int maxWidth,
                                                              const QStyleOptionViewItem &option) const
{
    // TODO
    return {};
}

TextAutoGenerateAttachmentDelegateHelperImage::ImageLayout
TextAutoGenerateAttachmentDelegateHelperImage::layoutImage(const TextAutoGenerateText::TextAutoGenerateAttachment &msgAttach,
                                                           const QStyleOptionViewItem &option,
                                                           int attachmentsWidth,
                                                           int attachmentsHeight) const
{
    ImageLayout layout;
    // TODO
    return layout;
}

#include "moc_textautogenerateattachmentdelegatehelperimage.cpp"
