/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratehistorylistview.h"

#include "core/models/textautogeneratechatsmodel.h"
#include "core/models/textautogeneratehistorylistheadingsproxymodel.h"
#include "core/models/textautogeneratehistorysortfilterproxymodel.h"
#include "core/textautogeneratemanager.h"
#include "delegate/textautogeneratehistorylistviewdelegate.h"
#include "textautogeneratechatwaitingansweranimation.h"
#include "textautogeneratetextwidget_animation_debug.h"
#include <KLocalizedString>
#include <KMessageBox>
#include <QContextMenuEvent>
#include <QMenu>
#include <qpainter.h>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateHistoryListView::TextAutoGenerateHistoryListView(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QTreeView(parent)
    , mHistoryProxyModel(new TextAutoGenerateHistorySortFilterProxyModel(this))
    , mHistoryListHeadingsProxyModel(new TextAutoGenerateHistoryListHeadingsProxyModel(this))
    , mManager(manager)
    , mDelegate(new TextAutoGenerateHistoryListViewDelegate(this))
{
    setHeaderHidden(true);
    setDragEnabled(false);
    setIndentation(0);
    setRootIsDecorated(false);
    setItemsExpandable(true);
    setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    setItemDelegate(mDelegate);

    if (mManager) {
        mHistoryListHeadingsProxyModel->setSourceModel(mManager->textAutoGenerateChatsModel());
        connect(mManager, &TextAutoGenerateText::TextAutoGenerateManager::showArchiveChanged, this, &TextAutoGenerateHistoryListView::slotShowArchived);
        connect(mManager,
                &TextAutoGenerateText::TextAutoGenerateManager::currentChatIdChanged,
                this,
                &TextAutoGenerateHistoryListView::slotCurrentChatIdChanged);

        connect(mManager->textAutoGenerateChatsModel(),
                &QAbstractItemModel::dataChanged,
                this,
                [this](const QModelIndex &topLeft, const QModelIndex &, const QList<int> &roles) {
                    if (roles.contains(TextAutoGenerateChatsModel::InProgress)) {
                        const bool inProgress = topLeft.data(TextAutoGenerateChatsModel::InProgress).toBool();
                        if (inProgress) {
                            addWaitingAnswerAnimation(topLeft);
                        }
                    }
                });
    }

    mHistoryProxyModel->setSourceModel(mHistoryListHeadingsProxyModel);
    setModel(mHistoryProxyModel);
    connect(model(), &QAbstractItemModel::rowsInserted, this, &QTreeView::expandAll);
    connect(model(), &QAbstractItemModel::modelReset, this, &QTreeView::expandAll);
    connect(model(), &QAbstractItemModel::rowsMoved, this, &QTreeView::expandAll);
    connect(model(), &QAbstractItemModel::layoutChanged, this, &QTreeView::expandAll);
    connect(selectionModel(), &QItemSelectionModel::currentChanged, this, &TextAutoGenerateHistoryListView::slotClicked);

    expandAll();
}

TextAutoGenerateHistoryListView::~TextAutoGenerateHistoryListView() = default;

void TextAutoGenerateHistoryListView::slotCurrentChatIdChanged()
{
    const QByteArray chatId = mManager->currentChatId();
    const int nSections = mHistoryProxyModel->rowCount();
    for (int sectionId = 0; sectionId < nSections; ++sectionId) {
        const auto section = mHistoryProxyModel->index(sectionId, 0, {});
        const auto sectionSize = mHistoryProxyModel->rowCount(section);

        for (int roomIdx = 0; roomIdx < sectionSize; ++roomIdx) {
            const auto roomModelIndex = mHistoryProxyModel->index(roomIdx, 0, section);
            const auto identifier = roomModelIndex.data(TextAutoGenerateChatsModel::Identifier).toByteArray();
            if (identifier == chatId) {
                selectionModel()->setCurrentIndex(roomModelIndex, QItemSelectionModel::ClearAndSelect | QItemSelectionModel::Rows);
            }
        }
    }
}

void TextAutoGenerateHistoryListView::slotShowArchived()
{
    mHistoryProxyModel->setShowArchived(mManager->showArchived());
}

void TextAutoGenerateHistoryListView::keyPressEvent(QKeyEvent *event)
{
    if (event->key() == Qt::Key_Escape) {
        event->accept();
    } else {
        QTreeView::keyPressEvent(event);
    }
}

void TextAutoGenerateHistoryListView::slotClicked(const QModelIndex &idx)
{
    if (idx.isValid()) {
        const QByteArray uuid = idx.data(TextAutoGenerateChatsModel::Identifier).toByteArray();
        if (!uuid.isEmpty()) {
            Q_EMIT switchToChat(uuid);
        }
    }
}

void TextAutoGenerateHistoryListView::contextMenuEvent(QContextMenuEvent *event)
{
    const bool isArchived = mManager ? mManager->showArchived() : false;
    QMenu menu(this);
    if (!isArchived) {
        auto newChatHistory = new QAction(QIcon::fromTheme(u"document-new"_s), i18nc("@action", "New Chat"), &menu);
        connect(newChatHistory, &QAction::triggered, this, [this]() {
            mManager->createNewChat();
        });
        menu.addAction(newChatHistory);
    }
    const QModelIndex index = indexAt(event->pos());
    if (index.parent().isValid()) {
        menu.addSeparator();

        if (index.isValid()) {
            auto renameHistory = new QAction(QIcon::fromTheme(u"document-edit"_s), i18nc("@action", "Modify…"), &menu);
            connect(renameHistory, &QAction::triggered, this, [index, this]() {
                const QByteArray uuid = index.data(TextAutoGenerateChatsModel::Identifier).toByteArray();
                if (!uuid.isEmpty()) {
                    edit(index);
                }
            });
            menu.addAction(renameHistory);

            menu.addSeparator();

            const bool isFavorite = index.data(TextAutoGenerateChatsModel::Favorite).toBool();
            auto changeFavoriteHistory =
                new QAction(QIcon::fromTheme(u"favorite"_s), isFavorite ? i18nc("@action", "Remove as Favorite") : i18nc("@action", "Set as Favorite"), &menu);
            connect(changeFavoriteHistory, &QAction::triggered, this, [index, isFavorite, this]() {
                const QByteArray uuid = index.data(TextAutoGenerateChatsModel::Identifier).toByteArray();
                if (!uuid.isEmpty()) {
                    mManager->changeFavoriteHistory(uuid, !isFavorite);
                }
            });
            menu.addAction(changeFavoriteHistory);

            const bool archived = index.data(TextAutoGenerateChatsModel::Archived).toBool();
            menu.addSeparator();
            auto archivedAction = new QAction(archived ? i18nc("@action", "Restore") : i18nc("@action", "Archive"), &menu);
            connect(archivedAction, &QAction::triggered, this, [index, archived, this]() {
                const QByteArray uuid = index.data(TextAutoGenerateChatsModel::Identifier).toByteArray();
                if (!uuid.isEmpty()) {
                    mManager->archiveDiscussion(uuid, !archived);
                }
            });
            menu.addAction(archivedAction);

            menu.addSeparator();

            auto removeHistory = new QAction(QIcon::fromTheme(u"list-remove"_s), i18nc("@action", "Remove…"), &menu);
            connect(removeHistory, &QAction::triggered, this, [index, this]() {
                if (KMessageBox::ButtonCode::PrimaryAction
                    == KMessageBox::questionTwoActions(this,
                                                       i18n("Do you want to remove this discussion?"),
                                                       i18nc("@title:window", "Remove Discussion"),
                                                       KStandardGuiItem::remove(),
                                                       KStandardGuiItem::cancel())) {
                    const QByteArray uuid = index.data(TextAutoGenerateChatsModel::Identifier).toByteArray();
                    if (!uuid.isEmpty()) {
                        mManager->removeDiscussion(mManager->currentChatId());
                    }
                }
            });
            menu.addAction(removeHistory);
        }
    }
    if (!menu.actions().isEmpty()) {
        menu.exec(event->globalPos());
    }
}

void TextAutoGenerateHistoryListView::slotSearchTextChanged(const QString &str)
{
    mHistoryProxyModel->setFilterFixedString(str);
}

void TextAutoGenerateHistoryListView::selectNextChat(Direction direction)
{
    // TODO
}

void TextAutoGenerateHistoryListView::paintEvent(QPaintEvent *event)
{
    if (mHistoryProxyModel->rowCount() == 0 && mHistoryProxyModel->showArchived()) {
        const QString label = i18n("No Archive Found.");

        QPainter p(viewport());

        QFont font = p.font();
        font.setItalic(true);
        p.setFont(font);

        if (!mTextColor.isValid()) {
            generalPaletteChanged();
        }
        p.setPen(mTextColor);
        p.drawText(QRect(0, 0, width(), height()), Qt::AlignCenter, label);
    } else {
        QTreeView::paintEvent(event);
    }
}

void TextAutoGenerateHistoryListView::generalPaletteChanged()
{
    const QPalette palette = viewport()->palette();
    QColor color = palette.text().color();
    color.setAlpha(128);
    mTextColor = color;
}

void TextAutoGenerateHistoryListView::addWaitingAnswerAnimation(const QModelIndex &index)
{
    auto animation = new TextAutoGenerateChatWaitingAnswerAnimation(mManager, this);
    animation->setModelIndex(index);
    const QMetaObject::Connection valueChangeConnection =
        connect(animation, &TextAutoGenerateChatWaitingAnswerAnimation::valueChanged, this, [this, animation]() {
            qCDebug(TEXTAUTOGENERATETEXT_WIDGET_ANIMATION_LOG) << "TextAutoGenerateChatWaitingAnswerAnimation valueChanged";
            mDelegate->needUpdateWaitingAnswerAnimation(animation->modelIndex(), animation->scaleOpacities());
            update(animation->modelIndex());
        });
    connect(animation, &TextAutoGenerateChatWaitingAnswerAnimation::waitingAnswerDone, this, [this, index, valueChangeConnection]() {
        mDelegate->removeNeedUpdateWaitingAnswerAnimation(index);
        disconnect(valueChangeConnection);
        qCDebug(TEXTAUTOGENERATETEXT_WIDGET_ANIMATION_LOG) << "TextAutoGenerateChatWaitingAnswerAnimation end";
        update(index);
    });
    animation->start();
}

#include "moc_textautogeneratehistorylistview.cpp"
