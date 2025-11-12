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
class TextAutoGenerateAttachment;
class TextAutoGenerateAttachmentDelegateHelperFile : public TextAutoGenerateAttachmentDelegateHelperBase
{
    Q_OBJECT
public:
    explicit TextAutoGenerateAttachmentDelegateHelperFile(QObject *parent = nullptr);
    ~TextAutoGenerateAttachmentDelegateHelperFile() override;

    void draw(const TextAutoGenerateText::TextAutoGenerateAttachment &msgAttach,
              QPainter *painter,
              QRect attachmentsRect,
              const QModelIndex &index,
              const QStyleOptionViewItem &option) const override;
    [[nodiscard]] QSize sizeHint(const TextAutoGenerateText::TextAutoGenerateAttachment &msgAttach,
                                 const QModelIndex &index,
                                 int maxWidth,
                                 const QStyleOptionViewItem &option) const override;

private:
    // TODO implement it
    struct FileLayout {
        QByteArray mimetype;
        QString name;
    };

    [[nodiscard]] TextAutoGenerateAttachmentDelegateHelperFile::FileLayout
    doLayout(const TextAutoGenerateText::TextAutoGenerateAttachment &msgAttach, const QStyleOptionViewItem &option, int attachmentsWidth) const;
};
}
