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
class TextAutoGenerateAttachmentDelegateHelperImage : public TextAutoGenerateAttachmentDelegateHelperBase
{
    Q_OBJECT
public:
    explicit TextAutoGenerateAttachmentDelegateHelperImage(QObject *parent = nullptr);
    ~TextAutoGenerateAttachmentDelegateHelperImage() override;

    void draw(QPainter *painter, QRect attachmentsRect, const QModelIndex &index, const QStyleOptionViewItem &option) const override;
    [[nodiscard]] QSize
    sizeHint(TextAutoGenerateText::TextAutoGenerateAttachment *att, const QModelIndex &index, int maxWidth, const QStyleOptionViewItem &option) const override;

private:
    // TODO implement it
    struct ImageLayout {
        QPixmap pixmap;
        QSize imageSize;
    };
};
}
