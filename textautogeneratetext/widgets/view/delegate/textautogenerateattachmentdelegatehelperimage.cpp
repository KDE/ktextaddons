/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogenerateattachmentdelegatehelperimage.h"

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateAttachmentDelegateHelperImage::TextAutoGenerateAttachmentDelegateHelperImage(QObject *parent)
    : TextAutoGenerateAttachmentDelegateHelperBase{parent}
{
}

TextAutoGenerateAttachmentDelegateHelperImage::~TextAutoGenerateAttachmentDelegateHelperImage() = default;

void TextAutoGenerateAttachmentDelegateHelperImage::draw(QPainter *painter,
                                                         QRect attachmentsRect,
                                                         const QModelIndex &index,
                                                         const QStyleOptionViewItem &option) const
{
    // TODO
}

QSize TextAutoGenerateAttachmentDelegateHelperImage::sizeHint(TextAutoGenerateText::TextAutoGenerateAttachment *att,
                                                              const QModelIndex &index,
                                                              int maxWidth,
                                                              const QStyleOptionViewItem &option) const
{
    // TODO
    return {};
}

#include "moc_textautogenerateattachmentdelegatehelperimage.cpp"
