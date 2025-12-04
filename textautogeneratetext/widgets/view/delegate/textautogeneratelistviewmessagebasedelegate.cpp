/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelistviewmessagebasedelegate.h"
#include "textautogeneratetextwidget_debug.h"

using namespace TextAutoGenerateText;
TextAutoGenerateListViewMessageBaseDelegate::TextAutoGenerateListViewMessageBaseDelegate(TextAutoGenerateText::TextAutoGenerateManager *manager,
                                                                                         QListView *view)
    : TextAutoGenerateText::TextAutoGenerateListViewBaseDelegate(view)
    , mHelperImage(new TextAutoGenerateAttachmentDelegateHelperImage(manager, this))
    , mHelperFile(new TextAutoGenerateAttachmentDelegateHelperFile(manager, this))
{
}

TextAutoGenerateListViewMessageBaseDelegate::~TextAutoGenerateListViewMessageBaseDelegate() = default;

TextAutoGenerateAttachmentDelegateHelperBase *
TextAutoGenerateListViewMessageBaseDelegate::attachmentsHelper(const TextAutoGenerateText::TextAutoGenerateAttachment &att) const
{
    switch (att.attachmentType()) {
    case TextAutoGenerateAttachment::AttachmentType::File:
        return mHelperFile.get();
    case TextAutoGenerateAttachment::AttachmentType::Image:
        return mHelperImage.get();
    case TextAutoGenerateAttachment::AttachmentType::Audio:
    case TextAutoGenerateAttachment::AttachmentType::Video:
        qCWarning(TEXTAUTOGENERATETEXT_WIDGET_LOG) << "not implemented type " << att.attachmentType() << " yet.";
        break;
    case TextAutoGenerateAttachment::AttachmentType::Unknown:
        break;
    }
    return nullptr;
}
