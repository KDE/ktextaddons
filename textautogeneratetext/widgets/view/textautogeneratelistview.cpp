/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelistview.h"
#include "core/textautogeneratechatmodel.h"
#include "core/textautogeneratemanager.h"
#include "textautogeneratelistviewdelegate.h"
#include <KLocalizedString>
#include <QApplication>
#include <QClipboard>
#include <QMenu>
#include <QMouseEvent>
#include <QScrollBar>
#include <QToolTip>

using namespace TextAutogenerateText;
TextAutogenerateListView::TextAutogenerateListView(QWidget *parent)
    : QListView(parent)
    , mDelegate(new TextAutogenerateListViewDelegate(this))
{
    setItemDelegate(mDelegate);
    setModel(TextAutogenerateManager::self()->textAutoGenerateChatModel());

    connect(TextAutogenerateManager::self()->textAutoGenerateChatModel(), &TextAutoGenerateChatModel::conversationCleared, this, [this]() {
        mDelegate->clearCache();
    });

    connect(TextAutogenerateManager::self()->textAutoGenerateChatModel(),
            &QAbstractItemModel::dataChanged,
            this,
            [this](const QModelIndex &topLeft, const QModelIndex &, const QList<int> &roles) {
                if (roles.contains(TextAutoGenerateChatModel::MessageRole) || roles.contains(TextAutoGenerateChatModel::FinishedRole)) {
                    const QByteArray uuid = topLeft.data(TextAutoGenerateChatModel::UuidRole).toByteArray();
                    if (!uuid.isEmpty()) {
                        mDelegate->removeMessageCache(uuid);
                    }
                }
            });
}

TextAutogenerateListView::~TextAutogenerateListView()
{
    TextAutogenerateManager::self()->textAutoGenerateChatModel()->resetConversation();
}

void TextAutogenerateListView::setMessages(const QList<TextAutoGenerateMessage> &msg)
{
    TextAutogenerateManager::self()->textAutoGenerateChatModel()->setMessages(msg);
}

void TextAutogenerateListView::contextMenuEvent(QContextMenuEvent *event)
{
    QMenu menu(this);
    const QModelIndex index = indexAt(event->pos());
    if (index.isValid()) {
        auto copy = new QAction(QIcon::fromTheme(QStringLiteral("edit-copy")), i18nc("@action", "Copy"), &menu);
        connect(copy, &QAction::triggered, this, [index]() {
            const QString currentValue = index.data().toString();
            QClipboard *clip = QApplication::clipboard();
            clip->setText(currentValue, QClipboard::Clipboard);
            clip->setText(currentValue, QClipboard::Selection);
        });
        menu.addAction(copy);
        menu.addSeparator();
        auto selectAllAction = new QAction(QIcon::fromTheme(QStringLiteral("edit-select-all")), i18nc("@action", "Select All"), &menu);
        connect(selectAllAction, &QAction::triggered, this, [this, index]() {
            slotSelectAll(index);
        });
        menu.addAction(selectAllAction);
    }
    if (!menu.actions().isEmpty()) {
        menu.exec(event->globalPos());
    }
}

void TextAutogenerateListView::slotSelectAll(const QModelIndex &index)
{
    mDelegate->selectAll(listViewOptions(), index);
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
    return mDelegate->mouseEvent(event, option, index);
}

#include "moc_textautogeneratelistview.cpp"
