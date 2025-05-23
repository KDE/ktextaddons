/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "widgets/view/textautogeneratelistviewbasedelegate.h"
#include <QObject>

class OllamaModelInfosDelegate : public TextAutoGenerateText::TextAutoGenerateListViewBaseDelegate
{
    Q_OBJECT
public:
    explicit OllamaModelInfosDelegate(QListView *view);
    ~OllamaModelInfosDelegate() override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    [[nodiscard]] bool mouseEvent(QEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index) override;
    [[nodiscard]] bool maybeStartDrag(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index) override;
    [[nodiscard]] bool helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index) override;

    [[nodiscard]] QTextDocument *documentForIndex(const QModelIndex &index, int width) const override;
    [[nodiscard]] QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    struct ModelInfoLayout {
        // Text
        QRect textRect;
        qreal baseLine; // used to draw sender/timestamp
    };
    void draw(QPainter *painter, const OllamaModelInfosDelegate::ModelInfoLayout &layout, const QModelIndex &index, const QStyleOptionViewItem &option) const;

    [[nodiscard]] OllamaModelInfosDelegate::ModelInfoLayout doLayout(const QStyleOptionViewItem &option, const QModelIndex &index) const;
};
