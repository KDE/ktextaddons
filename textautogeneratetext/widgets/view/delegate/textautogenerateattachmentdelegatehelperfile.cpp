/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogenerateattachmentdelegatehelperfile.h"

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateAttachmentDelegateHelperFile::TextAutoGenerateAttachmentDelegateHelperFile(QObject *parent)
    : TextAutoGenerateAttachmentDelegateHelperBase{parent}
{
}

TextAutoGenerateAttachmentDelegateHelperFile::~TextAutoGenerateAttachmentDelegateHelperFile() = default;

void TextAutoGenerateAttachmentDelegateHelperFile::draw(QPainter *painter,
                                                        QRect attachmentsRect,
                                                        const QModelIndex &index,
                                                        const QStyleOptionViewItem &option) const
{
    // TODO
}

QSize TextAutoGenerateAttachmentDelegateHelperFile::sizeHint(const QModelIndex &index, int maxWidth, const QStyleOptionViewItem &option) const
{
    // TODO
    return {};
}

#include "moc_textautogenerateattachmentdelegatehelperfile.cpp"
