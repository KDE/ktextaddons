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

using namespace TextAutoGenerateText;
TextAutoGenerateListView::TextAutoGenerateListView(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QListView(parent)
    , mDelegate(new TextAutoGenerateListViewDelegate(this))
    , mManager(manager)
{
    setVerticalScrollMode(QAbstractItemView::ScrollPerPixel); // nicer in case of huge messages
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setWordWrap(true); // so that the delegate sizeHint is called again when the width changes
    setItemDelegate(mDelegate);
    setFocusPolicy(Qt::NoFocus);
    scrollToBottom();
    setMouseTracking(true);
    if (mManager) {
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::currentChatIdChanged, this, &TextAutoGenerateListView::slotCurrentChatIdChanged);
    }

    connect(mDelegate, &TextAutoGenerateListViewDelegate::updateView, this, [this](const QModelIndex &index) {
        update(index);
    });

    connect(mDelegate, &TextAutoGenerateListViewDelegate::editMessage, this, &TextAutoGenerateListView::slotEditMessage);
    connect(mDelegate, &TextAutoGenerateListViewDelegate::copyMessage, this, &TextAutoGenerateListView::slotCopyMessage);
    connect(mDelegate, &TextAutoGenerateListViewDelegate::cancelRequested, this, &TextAutoGenerateListView::slotCancelRequested);
    connect(mDelegate, &TextAutoGenerateListViewDelegate::refreshRequested, this, &TextAutoGenerateListView::slotRefreshRequested);

    // Connect to rangeChanged rather than rowsInserted/rowsRemoved/modelReset.
    // This way it also catches the case of an item changing height (e.g. after async image loading)
    connect(verticalScrollBar(), &QScrollBar::rangeChanged, this, &TextAutoGenerateListView::maybeScrollToBottom);
}

TextAutoGenerateListView::~TextAutoGenerateListView() = default;

void TextAutoGenerateListView::slotEditMessage(const QModelIndex &index)
{
    auto model = const_cast<QAbstractItemModel *>(index.model());
    model->setData(index, true, TextAutoGenerateMessagesModel::EditingRole);
    Q_EMIT editMessageRequested(index);
}

void TextAutoGenerateListView::slotCancelRequested(const QModelIndex &index)
{
    const QByteArray uuid = index.data(TextAutoGenerateMessagesModel::UuidRole).toByteArray();
    if (!uuid.isEmpty()) {
        if (mManager->cancelRequest(mManager->currentChatId(), index)) {
            Q_EMIT cancelRequested(uuid);
        }
    }
}

void TextAutoGenerateListView::slotRefreshRequested(const QModelIndex &index)
{
    const QByteArray uuid = index.data(TextAutoGenerateMessagesModel::UuidRole).toByteArray();
    if (!uuid.isEmpty()) {
        const QByteArray chatId = mManager->currentChatId();
        const QModelIndex index = mManager->refreshAnswer(chatId, uuid);
        if (index.isValid()) {
            Q_EMIT refreshAnswerRequested(chatId, index);
        }
    }
}

void TextAutoGenerateListView::slotCopyMessage(const QModelIndex &index)
{
    const QString currentValue = index.data().toString();
    QClipboard *clip = QApplication::clipboard();
    clip->setText(currentValue, QClipboard::Clipboard);
    clip->setText(currentValue, QClipboard::Selection);
}

void TextAutoGenerateListView::contextMenuEvent(QContextMenuEvent *event)
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

void TextAutoGenerateListView::slotSelectAll(const QModelIndex &index)
{
    mDelegate->selectAll(listViewOptions(), index);
}

void TextAutoGenerateListView::resizeEvent(QResizeEvent *ev)
{
    QListView::resizeEvent(ev);

    // Fix not being really at bottom when the view gets reduced by the header widget becoming taller
    checkIfAtBottom();
    maybeScrollToBottom(); // this forces a layout in QAIV, which then changes the vbar max value
    updateVerticalPageStep();
    mDelegate->clearSizeHintCache();
}

void TextAutoGenerateListView::checkIfAtBottom()
{
    auto *vbar = verticalScrollBar();
    mAtBottom = vbar->value() == vbar->maximum();
}

void TextAutoGenerateListView::maybeScrollToBottom()
{
    if (mAtBottom) {
        scrollToBottom();
    }
}

void TextAutoGenerateListView::updateVerticalPageStep()
{
    verticalScrollBar()->setPageStep(viewport()->height() * 3 / 4);
}

void TextAutoGenerateListView::mouseReleaseEvent(QMouseEvent *event)
{
    handleMouseEvent(event);
}

void TextAutoGenerateListView::mouseDoubleClickEvent(QMouseEvent *event)
{
    handleMouseEvent(event);
}

void TextAutoGenerateListView::mousePressEvent(QMouseEvent *event)
{
    mPressedPosition = event->pos();
    handleMouseEvent(event);
}

void TextAutoGenerateListView::mouseMoveEvent(QMouseEvent *event)
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

QStyleOptionViewItem TextAutoGenerateListView::listViewOptions() const
{
    QStyleOptionViewItem option;
    initViewItemOption(&option);
    return option;
}

void TextAutoGenerateListView::handleMouseEvent(QMouseEvent *event)
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

bool TextAutoGenerateListView::maybeStartDrag(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    return mDelegate->maybeStartDrag(event, option, index);
}

bool TextAutoGenerateListView::mouseEvent(QMouseEvent *event, const QStyleOptionViewItem &option, const QModelIndex &index)
{
    return mDelegate->mouseEvent(event, option, index);
}

void TextAutoGenerateListView::leaveEvent(QEvent *event)
{
    if (mCurrentIndex.isValid()) {
        auto lastModel = const_cast<QAbstractItemModel *>(mCurrentIndex.model());
        lastModel->setData(mCurrentIndex, false, TextAutoGenerateMessagesModel::MouseHoverRole);
        mCurrentIndex = QPersistentModelIndex();
    }
    QListView::leaveEvent(event);
}

void TextAutoGenerateListView::handleKeyPressEvent(QKeyEvent *ev)
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

void TextAutoGenerateListView::scrollTo(const QModelIndex &index, QAbstractItemView::ScrollHint hint)
{
    QListView::scrollTo(index, hint);
    addSelectedMessageBackgroundAnimation(index);
}

void TextAutoGenerateListView::editingFinished(const QByteArray &uuid)
{
    auto model = mManager->messagesModelFromChatId(mManager->currentChatId());
    if (model) {
        const QModelIndex idx = model->indexForUuid(uuid);
        if (idx.isValid()) {
            auto lastModel = const_cast<QAbstractItemModel *>(idx.model());
            lastModel->setData(idx, false, TextAutoGenerateMessagesModel::EditingRole);
        }
    }
}

void TextAutoGenerateListView::slotCurrentChatIdChanged()
{
    auto model = mManager->messagesModelFromChatId(mManager->currentChatId());
    setModel(model);
}

void TextAutoGenerateListView::addWaitingAnswerAnimation(const QModelIndex &index)
{
    auto animation = new TextAutoGenerateMessageWaitingAnswerAnimation(mManager->currentChatId(), mManager, this);
    animation->setModelIndex(index);
    connect(animation, &TextAutoGenerateMessageWaitingAnswerAnimation::valueChanged, this, [this, animation]() {
        qCDebug(TEXTAUTOGENERATETEXT_WIDGET_ANIMATION_LOG) << "TextAutoGenerateMessageWaitingAnswerAnimation start";
        mDelegate->needUpdateWaitingAnswerAnimation(animation->modelIndex(), animation->scaleOpacities());
        update(animation->modelIndex());
    });
    connect(animation, &TextAutoGenerateMessageWaitingAnswerAnimation::waitingAnswerDone, this, [this, index]() {
        mDelegate->removeNeedUpdateWaitingAnswerAnimation(index);
        qCDebug(TEXTAUTOGENERATETEXT_WIDGET_ANIMATION_LOG) << "TextAutoGenerateMessageWaitingAnswerAnimation end";
        update(index);
    });
    animation->start();
}

void TextAutoGenerateListView::addSelectedMessageBackgroundAnimation(const QModelIndex &index)
{
    auto animation = new TextAutoGenerateSelectedMessageBackgroundAnimation(this);
    animation->setModelIndex(index);
    connect(animation, &TextAutoGenerateSelectedMessageBackgroundAnimation::backgroundColorChanged, this, [this, animation]() {
        qCDebug(TEXTAUTOGENERATETEXT_WIDGET_ANIMATION_LOG) << "TextAutoGenerateSelectedMessageBackgroundAnimation start";
        mDelegate->needUpdateIndexBackground(animation->modelIndex(), animation->backgroundColor());
        update(animation->modelIndex());
    });
    connect(animation, &TextAutoGenerateSelectedMessageBackgroundAnimation::animationFinished, this, [this, animation]() {
        qCDebug(TEXTAUTOGENERATETEXT_WIDGET_ANIMATION_LOG) << "TextAutoGenerateSelectedMessageBackgroundAnimation end";
        mDelegate->removeNeedUpdateIndexBackground(animation->modelIndex());
        update(animation->modelIndex());
    });
    animation->start();
}

void TextAutoGenerateListView::setModel(QAbstractItemModel *newModel)
{
    QAbstractItemModel *oldModel = model();
    if (oldModel) {
        disconnect(oldModel, nullptr, this, nullptr);
    }
    QListView::setModel(newModel);
    if (newModel) {
        connect(newModel, &QAbstractItemModel::rowsAboutToBeInserted, this, &TextAutoGenerateListView::checkIfAtBottom);
        connect(newModel, &QAbstractItemModel::rowsAboutToBeRemoved, this, &TextAutoGenerateListView::checkIfAtBottom);
        connect(newModel, &QAbstractItemModel::modelAboutToBeReset, this, &TextAutoGenerateListView::checkIfAtBottom);
        // Connect to rangeChanged rather than rowsInserted/rowsRemoved/modelReset.
        // This way it also catches the case of an item changing height (e.g. after async image loading)
        connect(verticalScrollBar(), &QScrollBar::rangeChanged, this, &TextAutoGenerateListView::maybeScrollToBottom);

        connect(newModel, &QAbstractItemModel::dataChanged, this, [this](const QModelIndex &topLeft, const QModelIndex &, const QList<int> &roles) {
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

        scrollToBottom();
    }
}

#include "moc_textautogeneratelistview.cpp"
