/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogenerateplugincommon_export.h"
#include "widgets/view/delegate/textautogeneratelistviewbasedelegate.h"

class TEXTAUTOGENERATEPLUGINCOMMON_EXPORT PluginCommonModelInstalledInfosDelegate : public TextAutoGenerateText::TextAutoGenerateListViewBaseDelegate
{
    Q_OBJECT
public:
    explicit PluginCommonModelInstalledInfosDelegate(QListView *view);
    ~PluginCommonModelInstalledInfosDelegate() override;

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
        QRect categoryRect;
    };
    void draw(QPainter *painter,
              const PluginCommonModelInstalledInfosDelegate::ModelInfoLayout &layout,
              const QModelIndex &index,
              const QStyleOptionViewItem &option) const;
    void drawCategories(QPainter *painter,
                        const PluginCommonModelInstalledInfosDelegate::ModelInfoLayout &layout,
                        const QModelIndex &index,
                        const QStyleOptionViewItem &option) const;

    [[nodiscard]] PluginCommonModelInstalledInfosDelegate::ModelInfoLayout doLayout(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    [[nodiscard]] bool handleMouseEvent(QMouseEvent *mouseEvent, QRect messageRect, const QStyleOptionViewItem &option, const QModelIndex &index);
};
