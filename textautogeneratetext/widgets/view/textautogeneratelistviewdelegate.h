/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "lrucache.h"
#include "textautogeneratemessagewaitingansweranimation.h"
#include <QItemDelegate>
#include <QTextDocument>
#include <memory>
class QListView;
namespace TextAutoGenerateText
{
class TextAutogenerateListViewTextSelection;
class TextAutogenerateListViewDelegate : public QItemDelegate
{
    Q_OBJECT
public:
    explicit TextAutogenerateListViewDelegate(QListView *view);
    ~TextAutogenerateListViewDelegate() override;

    void paint(QPainter *painter, const QStyleOptionViewItem &option, const QModelIndex &index) const override;
    [[nodiscard]] QSize sizeHint(const QStyleOptionViewItem &option, const QModelIndex &index) const override;

    void clearSizeHintCache();

    void removeMessageCache(const QByteArray &uuid);

    void clearCache();

    void selectAll(const QStyleOptionViewItem &option, const QModelIndex &index);

    [[nodiscard]] bool mouseEvent(QEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index);
    [[nodiscard]] bool helpEvent(QHelpEvent *event, QAbstractItemView *view, const QStyleOptionViewItem &option, const QModelIndex &index) override;
    [[nodiscard]] bool maybeStartDrag(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index);

    [[nodiscard]] QString selectedText() const;
    [[nodiscard]] bool hasSelection() const;
    [[nodiscard]] QTextDocument *documentForIndex(const QModelIndex &index, int width) const;

    void needUpdateIndexBackground(const QPersistentModelIndex &index, const QColor &color);
    void removeNeedUpdateIndexBackground(const QPersistentModelIndex &index);
    void needUpdateWaitingAnswerAnimation(const QPersistentModelIndex &index,
                                          const QList<TextAutogenerateMessageWaitingAnswerAnimation::ScaleAndOpacity> &scaleAndOpacities);
    void removeNeedUpdateWaitingAnswerAnimation(const QPersistentModelIndex &index);
Q_SIGNALS:
    void updateView(const QModelIndex &index);
    void editMessage(const QModelIndex &index);
    void removeMessage(const QModelIndex &index);
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

        // Remove icon
        QRect removeIconRect;

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

    [[nodiscard]] QSize sizeHint(const QModelIndex &index, int maxWidth, const QStyleOptionViewItem &option, qreal *pBaseLine) const;
    [[nodiscard]] QSize textSizeHint(QTextDocument *doc, qreal *pBaseLine) const;
    [[nodiscard]] TextAutogenerateListViewDelegate::MessageLayout doLayout(const QStyleOptionViewItem &option, const QModelIndex &index) const;
    [[nodiscard]] std::unique_ptr<QTextDocument> createTextDocument(const QString &text, int width) const;
    void draw(QPainter *painter, const MessageLayout &layout, const QModelIndex &index, const QStyleOptionViewItem &option) const;
    [[nodiscard]] bool handleMouseEvent(QMouseEvent *mouseEvent, QRect messageRect, const QStyleOptionViewItem &option, const QModelIndex &index);
    [[nodiscard]] bool maybeStartDrag(QMouseEvent *mouseEvent, QRect messageRect, const QStyleOptionViewItem &option, const QModelIndex &index);
    void drawDateAndIcons(QPainter *painter, const QModelIndex &index, const QStyleOptionViewItem &option, const MessageLayout &layout) const;
    [[nodiscard]] int buttonIconSize(const QStyleOptionViewItem &option) const;
    void drawInProgressIndicator(QPainter *painter, const QModelIndex &index, const QStyleOptionViewItem &option, const MessageLayout &layout) const;
    void slotUpdateColors();

    const QIcon mEditedIcon;
    const QIcon mRemoveIcon;
    const QIcon mCopyIcon;
    const QIcon mCancelIcon;
    const QIcon mRefreshIcon;
    const QIcon mInformationIcon;

    QColor mEditingColorMode;

    // Cache SizeHint value
    // We need to clear it when we resize widget.
    mutable LRUCache<QByteArray, QSize> mSizeHintCache;
    struct IndexBackgroundColor {
        QPersistentModelIndex index;
        QColor color;
    };
    QList<IndexBackgroundColor> mIndexBackgroundColorList;

    struct IndexScaleAndOpacities {
        QPersistentModelIndex index;
        QList<TextAutogenerateMessageWaitingAnswerAnimation::ScaleAndOpacity> scaleAndOpacities;
    };
    QList<IndexScaleAndOpacities> mIndexScaleAndOpacitiesList;
    mutable LRUCache<QByteArray, std::unique_ptr<QTextDocument>> mDocumentCache;
    QAbstractItemView *const mListView;
    TextAutogenerateListViewTextSelection *const mTextSelection;
};
}
