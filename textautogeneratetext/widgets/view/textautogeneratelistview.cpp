/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelistview.h"
#include "core/textautogeneratechatmodel.h"
#include "core/textautogeneratemanager.h"
#include "textautogeneratelistviewdelegate.h"
#include <QScrollBar>

using namespace TextAutogenerateText;
TextAutogenerateListView::TextAutogenerateListView(QWidget *parent)
    : QListView(parent)
{
    setItemDelegate(new TextAutogenerateListViewDelegate(this));
    setModel(TextAutogenerateManager::self()->textAutoGenerateChatModel());
}

TextAutogenerateListView::~TextAutogenerateListView() = default;

void TextAutogenerateListView::setMessages(const QList<TextAutoGenerateMessage> &msg)
{
    TextAutogenerateManager::self()->textAutoGenerateChatModel()->setMessages(msg);
}

void TextAutogenerateListView::resizeEvent(QResizeEvent *ev)
{
    QListView::resizeEvent(ev);

    // Fix not being really at bottom when the view gets reduced by the header widget becoming taller
    checkIfAtBottom();
    maybeScrollToBottom(); // this forces a layout in QAIV, which then changes the vbar max value
    updateVerticalPageStep();
    // TODO Q_EMIT needToClearSizeHintCache();
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
    // TODO
}

void TextAutogenerateListView::mouseDoubleClickEvent(QMouseEvent *event)
{
    // TODO
}

void TextAutogenerateListView::mousePressEvent(QMouseEvent *event)
{
    // TODO
}

void TextAutogenerateListView::mouseMoveEvent(QMouseEvent *event)
{
    // TODO
}

#include "moc_textautogeneratelistview.cpp"
