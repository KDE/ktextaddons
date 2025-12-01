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

bool TextAutoGenerateAttachmentDelegateHelperBase::handleMouseEvent([[maybe_unused]] const TextAutoGenerateAttachment &msgAttach,
                                                                    [[maybe_unused]] QMouseEvent *mouseEvent,
                                                                    [[maybe_unused]] QRect attachmentsRect,
                                                                    [[maybe_unused]] const QStyleOptionViewItem &option,
                                                                    [[maybe_unused]] const QModelIndex &index)
{
    return false;
}

#include "moc_textautogenerateattachmentdelegatehelperbase.cpp"
