/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratelistviewbasedelegate.h"
#include "textautogeneratetext_private_export.h"
class QListView;
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateSearchListViewDelegate : public TextAutoGenerateListViewBaseDelegate
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSearchListViewDelegate(TextAutoGenerateManager *manager, QListView *view);
    ~TextAutoGenerateSearchListViewDelegate() override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    [[nodiscard]] QTextDocument *documentForIndex(const QModelIndex &index, int width) const override;
    [[nodiscard]] QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

Q_SIGNALS:
    void goToMessage(const QString &link);

private:
    struct MessageLayout {
        // Text message
        QRect textRect;
        // Decoration
        QRect decoRect;

        // TODO remove it ???
        qreal baseLine; // used to draw sender/timestamp
    };
    void draw(QPainter *painter, const MessageLayout &layout, const QModelIndex &index, const QStyleOptionViewItem &option) const;
    [[nodiscard]] TextAutoGenerateSearchListViewDelegate::MessageLayout doLayout(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    [[nodiscard]] bool mouseEvent(QEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index) override;
    [[nodiscard]] bool handleMouseEvent(QMouseEvent *mouseEvent, QRect messageRect, const QStyleOptionViewItem &option, const QModelIndex &index);
};
}
