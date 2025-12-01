/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once
#include <QObject>
#include <QStyleOptionViewItem>
class QPainter;
namespace TextAutoGenerateText
{
class TextAutoGenerateAttachment;
class TextAutoGenerateAttachmentDelegateHelperBase : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateAttachmentDelegateHelperBase(QObject *parent = nullptr);
    ~TextAutoGenerateAttachmentDelegateHelperBase() override;

    virtual void draw(const TextAutoGenerateText::TextAutoGenerateAttachment &msgAttach,
                      QPainter *painter,
                      QRect attachmentsRect,
                      const QModelIndex &index,
                      const QStyleOptionViewItem &option) const = 0;
    [[nodiscard]] virtual QSize sizeHint(const TextAutoGenerateText::TextAutoGenerateAttachment &msgAttach,
                                         const QModelIndex &index,
                                         int maxWidth,
                                         const QStyleOptionViewItem &option) const = 0;

    virtual bool handleMouseEvent(const TextAutoGenerateText::TextAutoGenerateAttachment &msgAttach,
                                  QMouseEvent *mouseEvent,
                                  QRect attachmentsRect,
                                  const QStyleOptionViewItem &option,
                                  const QModelIndex &index);

protected:
    [[nodiscard]] virtual QPoint adaptMousePosition(const QPoint &pos,
                                                    const TextAutoGenerateText::TextAutoGenerateAttachment &msgAttach,
                                                    QRect attachmentsRect,
                                                    const QStyleOptionViewItem &option) = 0;
};
}
