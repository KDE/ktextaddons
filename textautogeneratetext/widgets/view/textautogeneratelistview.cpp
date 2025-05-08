/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelistview.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratemessagesmodel.h"
#include "textautogeneratelistviewdelegate.h"
#include "textautogeneratemessagewaitingansweranimation.h"
#include "textautogenerateselectedmessagebackgroundanimation.h"
#include "textautogeneratetextwidget_animation_debug.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QApplication>
#include <QClipboard>
#include <QMenu>
#include <QMouseEvent>
#include <QScrollBar>

using namespace TextAutogenerateText;
TextAutogenerateListView::TextAutogenerateListView(QWidget *parent)
    : QListView(parent)
    , mDelegate(new TextAutogenerateListViewDelegate(this))
{
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel); // nicer in case of huge messages
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWordWrap(true); // so that the delegate sizeHint is called again when the width changes
    setItemDelegate(mDelegate);
    setFocusPolicy(Qt::NoFocus);
    scrollToBottom();
    setMouseTracking(true);
    TextAutogenerateManager::self()->loadHistory();
    setModel(TextAutogenerateManager::self()->textAutoGenerateChatModel());
    connect(TextAutogenerateManager::self()->textAutoGenerateChatModel(), &TextAutoGenerateMessagesModel::conversationCleared, this, [this]() {
        mDelegate->clearCache();
    });

    connect(mDelegate, &TextAutogenerateListViewDelegate::updateView, this, [this](const QModelIndex &index) {
        update(index);
    });

    connect(mDelegate, &TextAutogenerateListViewDelegate::removeMessage, this, &TextAutogenerateListView::slotRemoveMessage);
    connect(mDelegate, &TextAutogenerateListViewDelegate::editMessage, this, &TextAutogenerateListView::slotEditMessage);
    connect(mDelegate, &TextAutogenerateListViewDelegate::copyMessage, this, &TextAutogenerateListView::slotCopyMessage);
    connect(mDelegate, &TextAutogenerateListViewDelegate::cancelRequested, this, &TextAutogenerateListView::slotCancelRequested);
    connect(mDelegate, &TextAutogenerateListViewDelegate::refreshRequested, this, &TextAutogenerateListView::slotRefreshRequested);

    connect(TextAutogenerateManager::self()->textAutoGenerateChatModel(),
            &QAbstractItemModel::rowsAboutToBeInserted,
            this,
            &TextAutogenerateListView::checkIfAtBottom);
    connect(TextAutogenerateManager::self()->textAutoGenerateChatModel(),
            &QAbstractItemModel::rowsAboutToBeRemoved,
            this,
            &TextAutogenerateListView::checkIfAtBottom);
    connect(TextAutogenerateManager::self()->textAutoGenerateChatModel(),
            &QAbstractItemModel::modelAboutToBeReset,
            this,
            &TextAutogenerateListView::checkIfAtBottom);

    connect(TextAutogenerateManager::self()->textAutoGenerateChatModel(),
            &QAbstractItemModel::dataChanged,
            this,
            [this](const QModelIndex &topLeft, const QModelIndex &, const QList<int> &roles) {
                if (roles.contains(TextAutoGenerateMessagesModel::MessageRole) || roles.contains(TextAutoGenerateMessagesModel::FinishedRole)) {
                    const QByteArray uuid = topLeft.data(TextAutoGenerateMessagesModel::UuidRole).toByteArray();
                    if (!uuid.isEmpty()) {
                        mDelegate->removeMessageCache(uuid);
                    }
                    if (roles.contains(TextAutoGenerateMessagesModel::FinishedRole)) {
                        const bool inProgress = !topLeft.data(TextAutoGenerateMessagesModel::FinishedRole).toBool();
                        if (inProgress) {
                            addWaitingAnswerAnimation(topLeft);
                        }
                    }
                }
            });

    // Connect to rangeChanged rather than rowsInserted/rowsRemoved/modelReset.
    // This way it also catches the case of an item changing height (e.g. after async image loading)
    connect(verticalScrollBar(), &QScrollBar::rangeChanged, this, &TextAutogenerateListView::maybeScrollToBottom);
}

TextAutogenerateListView::~TextAutogenerateListView()
{
    TextAutogenerateManager::self()->saveHistory();
    // TextAutogenerateManager::self()->textAutoGenerateChatModel()->resetConversation();
}

void TextAutogenerateListView::slotEditMessage(const QModelIndex &index)
{
    auto model = const_cast<QAbstractItemModel *>(index.model());
    model->setData(index, true, TextAutoGenerateMessagesModel::EditingRole);
    Q_EMIT editMessageRequested(index);
}

void TextAutogenerateListView::slotRemoveMessage(const QModelIndex &index)
{
    if (KMessageBox::ButtonCode::PrimaryAction
        == KMessageBox::questionTwoActions(this,
                                           i18n("Do you want to remove this discussion?"),
                                           i18nc("@title:window", "Remove Discussion"),
                                           KStandardGuiItem::remove(),
                                           KStandardGuiItem::cancel())) {
        const QByteArray uuid = index.data(TextAutoGenerateMessagesModel::UuidRole).toByteArray();
        if (!uuid.isEmpty()) {
            Q_EMIT cancelRequested(uuid);
            TextAutogenerateManager::self()->textAutoGenerateChatModel()->removeDiscussion(uuid);
        }
    }
}

void TextAutogenerateListView::slotCancelRequested(const QModelIndex &index)
{
    const QByteArray uuid = index.data(TextAutoGenerateMessagesModel::UuidRole).toByteArray();
    if (!uuid.isEmpty()) {
        if (TextAutogenerateManager::self()->textAutoGenerateChatModel()->cancelRequest(index)) {
            Q_EMIT cancelRequested(uuid);
        }
    }
}

void TextAutogenerateListView::slotRefreshRequested(const QModelIndex &index)
{
    const QByteArray uuid = index.data(TextAutoGenerateMessagesModel::UuidRole).toByteArray();
    if (!uuid.isEmpty()) {
        const QModelIndex index = TextAutogenerateManager::self()->textAutoGenerateChatModel()->refreshAnswer(uuid);
        if (index.isValid()) {
            Q_EMIT refreshAnswerRequested(index);
        }
    }
}

void TextAutogenerateListView::slotCopyMessage(const QModelIndex &index)
{
    const QString currentValue = index.data().toString();
    QClipboard *clip = QApplication::clipboard();
    clip->setText(currentValue, QClipboard::Clipboard);
    clip->setText(currentValue, QClipboard::Selection);
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
        auto copyAction = new QAction(QIcon::fromTheme(QStringLiteral("edit-copy")),
                                      mDelegate->hasSelection() ? i18nc("@action", "Copy Selection") : i18nc("@action", "Copy"),
                                      &menu);
        copyAction->setShortcut(QKeySequence::Copy);
        connect(copyAction, &QAction::triggered, this, [index, this]() {
            slotCopyMessage(index);
        });
        menu.addAction(copyAction);
        menu.addSeparator();
        auto selectAllAction = new QAction(QIcon::fromTheme(QStringLiteral("edit-select-all")), i18nc("@action", "Select All"), &menu);
        connect(selectAllAction, &QAction::triggered, this, [this, index]() {
            slotSelectAll(index);
        });
        selectAllAction->setShortcut(QKeySequence::SelectAll);
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
        // When the cursor hovers another message, hide/show the reaction icon accordingly
        if (mCurrentIndex != index) {
            if (mCurrentIndex.isValid()) {
                auto lastModel = const_cast<QAbstractItemModel *>(mCurrentIndex.model());
                lastModel->setData(mCurrentIndex, false, TextAutoGenerateMessagesModel::MouseHoverRole);
            }
            mCurrentIndex = index;
            auto model = const_cast<QAbstractItemModel *>(mCurrentIndex.model());
            model->setData(mCurrentIndex, true, TextAutoGenerateMessagesModel::MouseHoverRole);
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
    return mDelegate->maybeStartDrag(event, option, index);
}

bool TextAutogenerateListView::mouseEvent(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    return mDelegate->mouseEvent(event, option, index);
}

void TextAutogenerateListView::leaveEvent(QEvent *event)
{
    if (mCurrentIndex.isValid()) {
        auto lastModel = const_cast<QAbstractItemModel *>(mCurrentIndex.model());
        lastModel->setData(mCurrentIndex, false, TextAutoGenerateMessagesModel::MouseHoverRole);
        mCurrentIndex = QPersistentModelIndex();
    }
    QListView::leaveEvent(event);
}

void TextAutogenerateListView::handleKeyPressEvent(QKeyEvent *ev)
{
    const int key = ev->key();
    if (key == Qt::Key_Up || key == Qt::Key_Down || key == Qt::Key_PageDown || key == Qt::Key_PageUp) {
        // QListView/QAIV PageUp/PageDown moves the current item, first inside visible bounds
        // before it triggers scrolling around. Let's just let the scrollarea handle it,
        // since we don't show the current item.
        QAbstractScrollArea::keyPressEvent(ev);
        ev->accept();
    } else if (ev->modifiers() & Qt::ControlModifier) {
        if (key == Qt::Key_Home) {
            scrollToTop();
            ev->accept();
        } else if (key == Qt::Key_End) {
            scrollToBottom();
            ev->accept();
        }
    }
}

void TextAutogenerateListView::slotGoToDiscussion(const QByteArray &uuid)
{
    const QModelIndex idx = TextAutogenerateManager::self()->textAutoGenerateChatModel()->indexForUuid(uuid);
    if (idx.isValid()) {
        scrollTo(idx);
    }
}

void TextAutogenerateListView::scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint)
{
    QListView::scrollTo(index, hint);
    addSelectedMessageBackgroundAnimation(index);
}

void TextAutogenerateListView::editingFinished(const QByteArray &uuid)
{
    const QModelIndex idx = TextAutogenerateManager::self()->textAutoGenerateChatModel()->indexForUuid(uuid);
    if (idx.isValid()) {
        auto lastModel = const_cast<QAbstractItemModel *>(idx.model());
        lastModel->setData(idx, false, TextAutoGenerateMessagesModel::EditingRole);
    }
}

void TextAutogenerateListView::addWaitingAnswerAnimation(const QModelIndex &index)
{
    auto animation = new TextAutogenerateMessageWaitingAnswerAnimation(this);
    animation->setModelIndex(index);
    connect(animation, &TextAutogenerateMessageWaitingAnswerAnimation::valueChanged, this, [this, animation]() {
        qCDebug(TEXTAUTOGENERATETEXT_WIDGET_ANIMATION_LOG) << "TextAutogenerateMessageWaitingAnswerAnimation start";
        mDelegate->needUpdateWaitingAnswerAnimation(animation->modelIndex(), animation->scaleOpacities());
        update(animation->modelIndex());
    });
    connect(animation, &TextAutogenerateMessageWaitingAnswerAnimation::waitingAnswerDone, this, [this, index]() {
        mDelegate->removeNeedUpdateWaitingAnswerAnimation(index);
        qCDebug(TEXTAUTOGENERATETEXT_WIDGET_ANIMATION_LOG) << "TextAutogenerateMessageWaitingAnswerAnimation end";
        update(index);
    });
    animation->start();
}

void TextAutogenerateListView::addSelectedMessageBackgroundAnimation(const QModelIndex &index)
{
    auto animation = new TextAutogenerateSelectedMessageBackgroundAnimation(this);
    animation->setModelIndex(index);
    connect(animation, &TextAutogenerateSelectedMessageBackgroundAnimation::backgroundColorChanged, this, [this, animation]() {
        qCDebug(TEXTAUTOGENERATETEXT_WIDGET_ANIMATION_LOG) << "TextAutogenerateSelectedMessageBackgroundAnimation start";
        mDelegate->needUpdateIndexBackground(animation->modelIndex(), animation->backgroundColor());
        update(animation->modelIndex());
    });
    connect(animation, &TextAutogenerateSelectedMessageBackgroundAnimation::animationFinished, this, [this, animation]() {
        qCDebug(TEXTAUTOGENERATETEXT_WIDGET_ANIMATION_LOG) << "TextAutogenerateSelectedMessageBackgroundAnimation end";
        mDelegate->removeNeedUpdateIndexBackground(animation->modelIndex());
        update(animation->modelIndex());
    });
    animation->start();
}
#include "moc_textautogeneratelistview.cpp"
