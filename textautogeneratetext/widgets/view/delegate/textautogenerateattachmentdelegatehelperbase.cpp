/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogenerateattachmentdelegatehelperbase.h"

using namespace TextAutoGenerateText;
TextAutoGenerateAttachmentDelegateHelperBase::TextAutoGenerateAttachmentDelegateHelperBase(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateAttachmentDelegateHelperBase::~TextAutoGenerateAttachmentDelegateHelperBase() = default;

bool TextAutoGenerateAttachmentDelegateHelperBase::handleMouseEvent(const TextAutoGenerateAttachment &msgAttach,
                                                                    QMouseEvent *mouseEvent,
                                                                    QRect attachmentsRect,
                                                                    const QStyleOptionViewItem &option,
                                                                    const QModelIndex &index)
{
    return false;
}

#include "moc_textautogenerateattachmentdelegatehelperbase.cpp"
