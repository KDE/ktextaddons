/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "widgets/view/textautogeneratelistviewbasedelegate.h"
#include <QObject>

class OllamaModelInstalledInfosDelegate : public TextAutoGenerateText::TextAutoGenerateListViewBaseDelegate
{
    Q_OBJECT
public:
    explicit OllamaModelInstalledInfosDelegate(QListView *view);
    ~OllamaModelInstalledInfosDelegate() override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    [[nodiscard]] bool mouseEvent(QEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index) override;
    [[nodiscard]] bool helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index) override;

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
    };
    void draw(QPainter *painter,
              const OllamaModelInstalledInfosDelegate::ModelInfoLayout &layout,
              const QModelIndex &index,
              const QStyleOptionViewItem &option) const;
    void drawCatergories(QPainter *painter,
                         const OllamaModelInstalledInfosDelegate::ModelInfoLayout &layout,
                         const QModelIndex &index,
                         const QStyleOptionViewItem &option) const;

    [[nodiscard]] OllamaModelInstalledInfosDelegate::ModelInfoLayout doLayout(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    [[nodiscard]] bool handleMouseEvent(QMouseEvent *mouseEvent, QRect messageRect, const QStyleOptionViewItem &option, const QModelIndex &index);
};
