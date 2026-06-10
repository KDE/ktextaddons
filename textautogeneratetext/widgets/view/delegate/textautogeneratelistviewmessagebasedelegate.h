/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <TextAutoGenerateText/TextAutoGenerateListViewBaseDelegate>

#include <QScopedPointer>
namespace TextAutoGenerateText
{
class TextAutoGenerateAttachmentDelegateHelperImage;
class TextAutoGenerateAttachmentDelegateHelperFile;
class TextAutoGenerateAttachmentDelegateHelperBase;
class TextAutoGenerateManager;
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateListViewMessageBaseDelegate : public TextAutoGenerateText::TextAutoGenerateListViewBaseDelegate
{
    Q_OBJECT
public:
    explicit TextAutoGenerateListViewMessageBaseDelegate(TextAutoGenerateText::TextAutoGenerateManager *manager, QListView *view);
    ~TextAutoGenerateListViewMessageBaseDelegate() override;

    /// @note Ownership is not transferred
    [[nodiscard]] TextAutoGenerateAttachmentDelegateHelperBase *attachmentsHelper(const TextAutoGenerateAttachment &att) const;

protected:
    QScopedPointer<TextAutoGenerateAttachmentDelegateHelperImage> mHelperImage;
    QScopedPointer<TextAutoGenerateAttachmentDelegateHelperFile> mHelperFile;
};
}
