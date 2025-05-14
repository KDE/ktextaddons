/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#include "textautogeneratebaselistview.h"
#include "widgets/view/textautogeneratelistviewbasedelegate.h"
#include <QApplication>
#include <QClipboard>
#include <QMouseEvent>
#include <QScrollBar>

using namespace TextAutoGenerateText;
TextAutoGenerateBaseListView::TextAutoGenerateBaseListView(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QListView(parent)
    , mManager(manager)
{
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel); // nicer in case of huge messages
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWordWrap(true); // so that the delegate sizeHint is called again when the width changes

    setFocusPolicy(Qt::NoFocus);
    scrollToBottom();
    setMouseTracking(true);
    // Connect to rangeChanged rather than rowsInserted/rowsRemoved/modelReset.
    // This way it also catches the case of an item changing height (e.g. after async image loading)
    connect(verticalScrollBar(), &QScrollBar::rangeChanged, this, &TextAutoGenerateBaseListView::maybeScrollToBottom);
}

TextAutoGenerateBaseListView::~TextAutoGenerateBaseListView() = default;

void TextAutoGenerateBaseListView::slotSelectAll(const QModelIndex &index)
{
    mDelegate->selectAll(listViewOptions(), index);
}

void TextAutoGenerateBaseListView::resizeEvent(QResizeEvent *ev)
{
    QListView::resizeEvent(ev);

    // Fix not being really at bottom when the view gets reduced by the header widget becoming taller
    checkIfAtBottom();
    maybeScrollToBottom(); // this forces a layout in QAIV, which then changes the vbar max value
    updateVerticalPageStep();
    mDelegate->clearSizeHintCache();
}

void TextAutoGenerateBaseListView::slotCopyMessage(const QModelIndex &index)
{
    const QString currentValue = index.data().toString();
    QClipboard *clip = QApplication::clipboard();
    clip->setText(currentValue, QClipboard::Clipboard);
    clip->setText(currentValue, QClipboard::Selection);
}

QStyleOptionViewItem TextAutoGenerateBaseListView::listViewOptions() const
{
    QStyleOptionViewItem option;
    initViewItemOption(&option);
    return option;
}

void TextAutoGenerateBaseListView::checkIfAtBottom()
{
    auto *vbar = verticalScrollBar();
    mAtBottom = vbar->value() == vbar->maximum();
}

void TextAutoGenerateBaseListView::maybeScrollToBottom()
{
    if (mAtBottom) {
        scrollToBottom();
    }
}

void TextAutoGenerateBaseListView::updateVerticalPageStep()
{
    verticalScrollBar()->setPageStep(viewport()->height() * 3 / 4);
}

bool TextAutoGenerateBaseListView::maybeStartDrag(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    return mDelegate->maybeStartDrag(event, option, index);
}

bool TextAutoGenerateBaseListView::mouseEvent(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    return mDelegate->mouseEvent(event, option, index);
}

void TextAutoGenerateBaseListView::mouseReleaseEvent(QMouseEvent *event)
{
    handleMouseEvent(event);
}

void TextAutoGenerateBaseListView::mouseDoubleClickEvent(QMouseEvent *event)
{
    handleMouseEvent(event);
}

void TextAutoGenerateBaseListView::mousePressEvent(QMouseEvent *event)
{
    mPressedPosition = event->pos();
    handleMouseEvent(event);
}

void TextAutoGenerateBaseListView::mouseMoveEvent(QMouseEvent *event)
{
    // Drag support
    const int distance = (event->pos() - mPressedPosition).manhattanLength();
    if (distance > QApplication::startDragDistance()) {
        mPressedPosition = {};
        const QPersistentModelIndex index = indexAt(event->pos());
        if (index.isValid()) {
            QStyleOptionViewItem options = listViewOptions();
            options.rect = visualRect(index);
            if (maybeStartDrag(event, options, index)) {
                return;
            }
        }
    }
    handleMouseEvent(event);
}

void TextAutoGenerateBaseListView::handleMouseEvent(QMouseEvent *event)
{
    const QPersistentModelIndex index = indexAt(event->pos());
    if (index.isValid()) {
        // When the cursor hovers another message, hide/show the reaction icon accordingly
        if (mCurrentIndex != index) {
            mCurrentIndex = index;
        }
        QStyleOptionViewItem options = listViewOptions();
        options.rect = visualRect(mCurrentIndex);
        if (mouseEvent(event, options, mCurrentIndex)) {
            update(mCurrentIndex);
        }
    }
}

#include "moc_textautogeneratebaselistview.cpp"
