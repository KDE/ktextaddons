/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollamacommon_export.h"
#include "widgets/view/delegate/textautogeneratelistviewbasedelegate.h"

class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonModelAvailableInfosDelegate : public TextAutoGenerateText::TextAutoGenerateListViewBaseDelegate
{
    Q_OBJECT
public:
    explicit OllamaCommonModelAvailableInfosDelegate(QListView *view);
    ~OllamaCommonModelAvailableInfosDelegate() override;

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
    TEXTAUTOGENERATEOLLAMACOMMON_NO_EXPORT void draw(QPainter *painter,
                                                     const OllamaCommonModelAvailableInfosDelegate::ModelInfoLayout &layout,
                                                     const QModelIndex &index,
                                                     const QStyleOptionViewItem &option) const;
    TEXTAUTOGENERATEOLLAMACOMMON_NO_EXPORT void drawCatergories(QPainter *painter,
                                                                const OllamaCommonModelAvailableInfosDelegate::ModelInfoLayout &layout,
                                                                const QModelIndex &index,
                                                                const QStyleOptionViewItem &option) const;

    [[nodiscard]] TEXTAUTOGENERATEOLLAMACOMMON_NO_EXPORT OllamaCommonModelAvailableInfosDelegate::ModelInfoLayout doLayout(const QStyleOptionViewItem &option,
                                                                                                                           const QModelIndex &index) const;
    [[nodiscard]] TEXTAUTOGENERATEOLLAMACOMMON_NO_EXPORT bool
    handleMouseEvent(QMouseEvent *mouseEvent, QRect messageRect, const QStyleOptionViewItem &option, const QModelIndex &index);
};
