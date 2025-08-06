/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelistview.h"
#include "core/models/textautogeneratemessagesmodel.h"
#include "core/textautogeneratemanager.h"
#include "textautogeneratelistviewdelegate.h"
#include "textautogeneratemessagewaitingansweranimation.h"
#include "textautogenerateselectedmessagebackgroundanimation.h"
#include "textautogeneratetextwidget_animation_debug.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QApplication>
#include <QClipboard>
#include <QMouseEvent>
#include <QScrollBar>
#include <TextAutoGenerateText/TextAutoGeneratePluginText>
#include <TextAutoGenerateText/TextAutoGeneratePluginTextManager>

using namespace TextAutoGenerateText;
TextAutoGenerateListView::TextAutoGenerateListView(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : TextAutoGenerateBaseListView(manager, parent)
{
    auto delegate = new TextAutoGenerateListViewDelegate(this);
    mDelegate = delegate;
    setItemDelegate(mDelegate);
    if (mManager) {
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::currentChatIdChanged, this, &TextAutoGenerateListView::slotCurrentChatIdChanged);
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::showArchiveChanged, this, [this, delegate]() {
            delegate->setShowArchive(mManager->showArchived());
        });
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::showMessageId, this, &TextAutoGenerateListView::goToMessageId);
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::chatInProgressChanged, this, [delegate](bool inProgress) {
            delegate->setInProgress(inProgress);
        });
    }

    QList<TextAutoGeneratePluginText *> plugins = TextAutoGeneratePluginTextManager::self()->pluginsList();
    if (plugins.count() > 1) {
        std::sort(plugins.begin(), plugins.end(), [](TextAutoGeneratePluginText *left, TextAutoGeneratePluginText *right) {
            return left->order() < right->order();
        });
    }
    /*
    for (TextAutoGeneratePluginText *plugin : plugins) {
        if (plugin->enabled()) {
            connect(plugin, &TextAutoGeneratePluginText::errorMessage, this, &MessageListViewBase::errorMessage);
            connect(plugin, &TextAutoGeneratePluginText::successMessage, this, &MessageListViewBase::successMessage);
            auto interface = plugin->createInterface(this);
            mPluginTextInterface.append(interface);
        }
    }
*/

    connect(delegate, &TextAutoGenerateListViewDelegate::updateView, this, &TextAutoGenerateListView::slotUpdateView);

    connect(delegate, &TextAutoGenerateListViewDelegate::editMessage, this, &TextAutoGenerateListView::slotEditMessage);
    connect(delegate, &TextAutoGenerateListViewDelegate::copyMessage, this, &TextAutoGenerateListView::slotCopyMessage);
    connect(delegate, &TextAutoGenerateListViewDelegate::cancelRequested, this, &TextAutoGenerateListView::slotCancelRequested);
    connect(delegate, &TextAutoGenerateListViewDelegate::refreshRequested, this, &TextAutoGenerateListView::slotRefreshRequested);
    connect(delegate, &TextAutoGenerateListViewDelegate::removeMessage, this, &TextAutoGenerateListView::slotRemoveRequested);
}

TextAutoGenerateListView::~TextAutoGenerateListView() = default;

void TextAutoGenerateListView::slotUpdateView()
{
    viewport()->update();
}

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

void TextAutoGenerateListView::slotRemoveRequested(const QModelIndex &index)
{
    const QByteArray uuid = index.data(TextAutoGenerateMessagesModel::UuidRole).toByteArray();
    if (!uuid.isEmpty()) {
        const QByteArray chatId = mManager->currentChatId();
        mManager->removeMessage(chatId, uuid);
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

void TextAutoGenerateListView::leaveEvent(QEvent *event)
{
    if (mCurrentIndex.isValid()) {
        auto lastModel = const_cast<QAbstractItemModel *>(mCurrentIndex.model());
        lastModel->setData(mCurrentIndex, false, TextAutoGenerateMessagesModel::MouseHoverRole);
        mCurrentIndex = QPersistentModelIndex();
    }
    QListView::leaveEvent(event);
}

QString TextAutoGenerateListView::originalMessage(const QModelIndex &index) const
{
    return index.data(TextAutoGenerateMessagesModel::OriginalMessageRole).toString();
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

void TextAutoGenerateListView::goToMessageId(const QByteArray &uuid)
{
    auto model = mManager->messagesModelFromChatId(mManager->currentChatId());
    if (model) {
        const QModelIndex idx = model->indexForUuid(uuid);
        if (idx.isValid()) {
            scrollTo(idx);
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
    // TODO get info
    static_cast<TextAutoGenerateListViewDelegate *>(mDelegate)->setInProgress(mManager->chatInProgress(mManager->currentChatId()));
}

void TextAutoGenerateListView::addWaitingAnswerAnimation(const QModelIndex &index)
{
    auto animation = new TextAutoGenerateMessageWaitingAnswerAnimation(mManager->currentChatId(), mManager, this);
    animation->setModelIndex(index);
    const QMetaObject::Connection valueChangeConnection =
        connect(animation, &TextAutoGenerateMessageWaitingAnswerAnimation::valueChanged, this, [this, animation]() {
            qCDebug(TEXTAUTOGENERATETEXT_WIDGET_ANIMATION_LOG) << "TextAutoGenerateMessageWaitingAnswerAnimation start";
            static_cast<TextAutoGenerateListViewDelegate *>(mDelegate)->needUpdateWaitingAnswerAnimation(animation->modelIndex(), animation->scaleOpacities());
            update(animation->modelIndex());
        });
    connect(animation, &TextAutoGenerateMessageWaitingAnswerAnimation::waitingAnswerDone, this, [this, index, valueChangeConnection]() {
        static_cast<TextAutoGenerateListViewDelegate *>(mDelegate)->removeNeedUpdateWaitingAnswerAnimation(index);
        disconnect(valueChangeConnection);
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
        static_cast<TextAutoGenerateListViewDelegate *>(mDelegate)->needUpdateIndexBackground(animation->modelIndex(), animation->backgroundColor());
        update(animation->modelIndex());
    });
    connect(animation, &TextAutoGenerateSelectedMessageBackgroundAnimation::animationFinished, this, [this, animation]() {
        qCDebug(TEXTAUTOGENERATETEXT_WIDGET_ANIMATION_LOG) << "TextAutoGenerateSelectedMessageBackgroundAnimation end";
        static_cast<TextAutoGenerateListViewDelegate *>(mDelegate)->removeNeedUpdateIndexBackground(animation->modelIndex());
        update(animation->modelIndex());
    });
    animation->start();
}

void TextAutoGenerateListView::setModel(QAbstractItemModel *newModel)
{
    const QAbstractItemModel *oldModel = model();
    if (oldModel) {
        disconnect(oldModel, nullptr, this, nullptr);
        mDelegate->clearSelection();
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
