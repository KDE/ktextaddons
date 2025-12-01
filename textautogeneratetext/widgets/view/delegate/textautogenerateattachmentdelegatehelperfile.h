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

    [[nodiscard]] bool handleMouseEvent(const TextAutoGenerateText::TextAutoGenerateAttachment &msgAttach,
                                        QMouseEvent *mouseEvent,
                                        QRect attachmentsRect,
                                        const QStyleOptionViewItem &option,
                                        const QModelIndex &index) override;

protected:
    [[nodiscard]] QPoint adaptMousePosition(const QPoint &pos,
                                            const TextAutoGenerateText::TextAutoGenerateAttachment &msgAttach,
                                            QRect attachmentsRect,
                                            const QStyleOptionViewItem &option) override;

private:
    struct FileLayout {
        QByteArray mimetype;
        QString name;
        QPixmap pixmap;
        QSize nameSize;
    };

    [[nodiscard]] TextAutoGenerateAttachmentDelegateHelperFile::FileLayout
    doLayout(const TextAutoGenerateText::TextAutoGenerateAttachment &msgAttach, const QStyleOptionViewItem &option, int attachmentsWidth) const;
};
}
