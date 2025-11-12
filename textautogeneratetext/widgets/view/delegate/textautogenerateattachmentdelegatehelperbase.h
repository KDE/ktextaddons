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
    [[nodiscard]] virtual QSize
    sizeHint(TextAutoGenerateText::TextAutoGenerateAttachment *att, const QModelIndex &index, int maxWidth, const QStyleOptionViewItem &option) const = 0;
};
}
