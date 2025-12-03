/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogenerateattachmentdelegatehelperfile.h"
#include "textautogenerateattachmentdelegatehelperimage.h"
#include "textautogeneratelistviewbasedelegate.h"
#include <QScopedPointer>
namespace TextAutoGenerateText
{
class TextAutoGenerateListViewMessageBaseDelegate : public TextAutoGenerateText::TextAutoGenerateListViewBaseDelegate
{
    Q_OBJECT
public:
    explicit TextAutoGenerateListViewMessageBaseDelegate(TextAutoGenerateText::TextAutoGenerateManager *manager, QListView *view);
    ~TextAutoGenerateListViewMessageBaseDelegate() override;

protected:
    QScopedPointer<TextAutoGenerateAttachmentDelegateHelperImage> mHelperImage;
    QScopedPointer<TextAutoGenerateAttachmentDelegateHelperFile> mHelperFile;
};
}
