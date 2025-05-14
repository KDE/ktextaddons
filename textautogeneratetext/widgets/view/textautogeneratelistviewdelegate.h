/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratelistviewbasedelegate.h"
#include "textautogeneratemessagewaitingansweranimation.h"
#include <QItemDelegate>
#include <QTextDocument>
#include <memory>
class QListView;
namespace TextAutoGenerateText
{
class TextAutoGenerateListViewTextSelection;
class TextAutoGenerateListViewDelegate : public TextAutoGenerateListViewBaseDelegate
{
    Q_OBJECT
public:
    explicit TextAutoGenerateListViewDelegate(QListView *view);
    ~TextAutoGenerateListViewDelegate() override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    [[nodiscard]] QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    [[nodiscard]] bool mouseEvent(QEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index);
    [[nodiscard]] bool helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index) override;
    [[nodiscard]] bool maybeStartDrag(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index);

    [[nodiscard]] QTextDocument *documentForIndex(const QModelIndex &index, int width) const override;

    void needUpdateIndexBackground(const QPersistentModelIndex &index, const QColor &color);
    void removeNeedUpdateIndexBackground(const QPersistentModelIndex &index);
    void needUpdateWaitingAnswerAnimation(const QPersistentModelIndex &index,
                                          const QList<TextAutoGenerateMessageWaitingAnswerAnimation::ScaleAndOpacity> &scaleAndOpacities);
    void removeNeedUpdateWaitingAnswerAnimation(const QPersistentModelIndex &index);
Q_SIGNALS:
    void editMessage(const QModelIndex &index);
    void copyMessage(const QModelIndex &index);
    void cancelRequested(const QModelIndex &index);
    void refreshRequested(const QModelIndex &index);

private:
    struct MessageLayout {
        // Text message
        QRect textRect;
        qreal baseLine; // used to draw sender/timestamp

        // Decoration
        QRect decoRect;

        // Date Size
        QSize dateSize;

        // Edited icon
        QRect editedIconRect;

        // Favorite icon
        QRect copyIconRect;

        // Cancel icon
        QRect cancelIconRect;

        // Refresh icon
        QRect refreshIconRect;

        // Info icon
        QRect infoIconRect;

        // Date Area
        QRect dateAreaRect;

        // In progress Area
        QRect inProgressRect;
    };

    [[nodiscard]] TextAutoGenerateListViewDelegate::MessageLayout doLayout(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    void draw(QPainter *painter, const MessageLayout &layout, const QModelIndex &index, const QStyleOptionViewItem &option) const;
    [[nodiscard]] bool handleMouseEvent(QMouseEvent *mouseEvent, QRect messageRect, const QStyleOptionViewItem &option, const QModelIndex &index);
    [[nodiscard]] bool maybeStartDrag(QMouseEvent *mouseEvent, QRect messageRect, const QStyleOptionViewItem &option, const QModelIndex &index);
    void drawDateAndIcons(QPainter *painter, const QModelIndex &index, const QStyleOptionViewItem &option, const MessageLayout &layout) const;
    [[nodiscard]] int buttonIconSize(const QStyleOptionViewItem &option) const;
    void drawInProgressIndicator(QPainter *painter, const QModelIndex &index, const QStyleOptionViewItem &option, const MessageLayout &layout) const;
    void slotUpdateColors();

    const QIcon mEditedIcon;
    const QIcon mCopyIcon;
    const QIcon mCancelIcon;
    const QIcon mRefreshIcon;
    const QIcon mInformationIcon;

    QColor mEditingColorMode;

    struct IndexBackgroundColor {
        QPersistentModelIndex index;
        QColor color;
    };
    QList<IndexBackgroundColor> mIndexBackgroundColorList;

    struct IndexScaleAndOpacities {
        QPersistentModelIndex index;
        QList<TextAutoGenerateMessageWaitingAnswerAnimation::ScaleAndOpacity> scaleAndOpacities;
    };
    QList<IndexScaleAndOpacities> mIndexScaleAndOpacitiesList;
};
}
