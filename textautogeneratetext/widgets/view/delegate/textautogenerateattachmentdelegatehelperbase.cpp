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

#include "moc_textautogenerateattachmentdelegatehelperbase.cpp"
