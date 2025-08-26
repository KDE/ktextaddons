/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "widgets/view/delegate/textautogeneratelistviewbasedelegate.h"
#include <QObject>

class OllamaModelAvailableInfosDelegate : public TextAutoGenerateText::TextAutoGenerateListViewBaseDelegate
{
    Q_OBJECT
public:
    explicit OllamaModelAvailableInfosDelegate(QListView *view);
    ~OllamaModelAvailableInfosDelegate() override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    [[nodiscard]] bool mouseEvent(QEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index) override;

    [[nodiscard]] QTextDocument *documentForIndex(const QModelIndex &index, int width) const override;
    [[nodiscard]] QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

private:
    struct CategoryLayout {
        QRectF categoryRect;
        QString categoryString;
    };

    struct ModelInfoLayout {
        // Text
        QRect textRect;
        qreal baseLine; // used to draw sender/timestamp

        QList<CategoryLayout> categoriesLayout;
        QRect categoryRect;
    };
    void draw(QPainter *painter,
              const OllamaModelAvailableInfosDelegate::ModelInfoLayout &layout,
              const QModelIndex &index,
              const QStyleOptionViewItem &option) const;
    void drawCatergories(QPainter *painter,
                         const OllamaModelAvailableInfosDelegate::ModelInfoLayout &layout,
                         const QModelIndex &index,
                         const QStyleOptionViewItem &option) const;

    [[nodiscard]] OllamaModelAvailableInfosDelegate::ModelInfoLayout doLayout(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    [[nodiscard]] bool handleMouseEvent(QMouseEvent *mouseEvent, QRect messageRect, const QStyleOptionViewItem &option, const QModelIndex &index);
};
