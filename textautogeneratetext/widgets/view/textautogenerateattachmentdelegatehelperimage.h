/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include "textautogenerateattachmentdelegatehelperbase.h"

#include <QObject>
#include <QStyleOptionViewItem>
class QPainter;
namespace TextAutoGenerateText
{
class TextAutoGenerateAttachmentDelegateHelperImage : public TextAutoGenerateAttachmentDelegateHelperBase
{
    Q_OBJECT
public:
    explicit TextAutoGenerateAttachmentDelegateHelperImage(QObject *parent = nullptr);
    ~TextAutoGenerateAttachmentDelegateHelperImage() override;
};
}
