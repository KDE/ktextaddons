/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelistview.h"
#include "core/textautogeneratechatmodel.h"
#include "core/textautogeneratemanager.h"
#include "textautogeneratelistviewdelegate.h"
#include <QApplication>
#include <QMouseEvent>
#include <QScrollBar>

using namespace TextAutogenerateText;
TextAutogenerateListView::TextAutogenerateListView(QWidget *parent)
    : QListView(parent)
    , mDelegate(new TextAutogenerateListViewDelegate(this))
{
    setItemDelegate(mDelegate);
    setModel(TextAutogenerateManager::self()->textAutoGenerateChatModel());
}

TextAutogenerateListView::~TextAutogenerateListView() = default;

void TextAutogenerateListView::setMessages(const QList<TextAutoGenerateMessage> &msg)
{
    TextAutogenerateManager::self()->textAutoGenerateChatModel()->setMessages(msg);
}

void TextAutogenerateListView::contextMenuEvent(QContextMenuEvent *event)
{
    // TODO
}

void TextAutogenerateListView::resizeEvent(QResizeEvent *ev)
{
    QListView::resizeEvent(ev);

    // Fix not being really at bottom when the view gets reduced by the header widget becoming taller
    checkIfAtBottom();
    maybeScrollToBottom(); // this forces a layout in QAIV, which then changes the vbar max value
    updateVerticalPageStep();
    mDelegate->clearSizeHintCache();
}

void TextAutogenerateListView::checkIfAtBottom()
{
    auto *vbar = verticalScrollBar();
    mAtBottom = vbar->value() == vbar->maximum();
}

void TextAutogenerateListView::maybeScrollToBottom()
{
    if (mAtBottom) {
        scrollToBottom();
    }
}

void TextAutogenerateListView::updateVerticalPageStep()
{
    verticalScrollBar()->setPageStep(viewport()->height() * 3 / 4);
}

void TextAutogenerateListView::mouseReleaseEvent(QMouseEvent *event)
{
    handleMouseEvent(event);
}

void TextAutogenerateListView::mouseDoubleClickEvent(QMouseEvent *event)
{
    handleMouseEvent(event);
}

void TextAutogenerateListView::mousePressEvent(QMouseEvent *event)
{
    mPressedPosition = event->pos();
    handleMouseEvent(event);
}

void TextAutogenerateListView::mouseMoveEvent(QMouseEvent *event)
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

QStyleOptionViewItem TextAutogenerateListView::listViewOptions() const
{
    QStyleOptionViewItem option;
    initViewItemOption(&option);
    return option;
}

void TextAutogenerateListView::handleMouseEvent(QMouseEvent *event)
{
    const QPersistentModelIndex index = indexAt(event->pos());
    if (index.isValid()) {
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

bool TextAutogenerateListView::maybeStartDrag(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    // TODO
    Q_UNUSED(event);
    Q_UNUSED(option);
    Q_UNUSED(index);
    return false;
}

bool TextAutogenerateListView::mouseEvent(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    // TODO
    Q_UNUSED(event);
    Q_UNUSED(option);
    Q_UNUSED(index);
    return false;
}

#include "moc_textautogeneratelistview.cpp"
