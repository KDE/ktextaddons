/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QStyledItemDelegate>
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class McpServerListViewDelegate : public QStyledItemDelegate
{
    Q_OBJECT
public:
    explicit McpServerListViewDelegate(QObject *parent = nullptr);
    ~McpServerListViewDelegate() override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    [[nodiscard]] QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;
};
}
