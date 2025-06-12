/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QStyledItemDelegate>
namespace TextAutoGenerateText
{
class TextAutoGenerateTextInstancesManagerListViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextInstancesManagerListViewDelegate(QObject *parent = nullptr);
    ~TextAutoGenerateTextInstancesManagerListViewDelegate() override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    [[nodiscard]] QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
}
