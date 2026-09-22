/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratehistorywidget.h"
#include "core/models/textautogeneratetagsmodel.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratetagsmanager.h"
#include "widgets/tags/textautogenerateselecttagscombobox.h"
#include "widgets/view/textautogeneratehistorylistview.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QLineEdit>
#include <QToolButton>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateHistoryWidget::TextAutoGenerateHistoryWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mTextAutoGenerateHistoryListView(new TextAutoGenerateHistoryListView(manager, this))
    , mSearchLineEdit(new QLineEdit(this))
    , mSelectTagsComboBox(new TextAutoGenerateSelectTagsComboBox(this))
    , mManager(manager)
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});
    mainLayout->setSpacing(0);

    const auto shortcut = QKeySequence(Qt::CTRL | Qt::Key_K);

    mSearchLineEdit->setObjectName("mSearchLineEdit"_L1);
    mSearchLineEdit->setClearButtonEnabled(true);
    mSearchLineEdit->addAction(QIcon::fromTheme(u"view-filter"_s), QLineEdit::LeadingPosition);
    mSearchLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Search… (%1)", shortcut.toString(QKeySequence::NativeText)));

    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);
    mainLayout->addWidget(mSearchLineEdit);

    auto selectTagsLayout = new QHBoxLayout;
    selectTagsLayout->setContentsMargins({});
    selectTagsLayout->setSpacing(0);
    mainLayout->addLayout(selectTagsLayout);
    mSelectTagsComboBox->setObjectName("mSelectTagsComboBox"_L1);
    mSelectTagsComboBox->setToolTip(i18nc("@info:tooltip", "Only show the chats which have one of the selected tags"));
    selectTagsLayout->addWidget(mSelectTagsComboBox);

    auto clearTags = new QToolButton(this);
    clearTags->setObjectName("clearTags"_L1);
    clearTags->setAutoRaise(true);
    clearTags->setIcon(QIcon::fromTheme(u"edit-clear-all"_s));
    selectTagsLayout->addWidget(clearTags);

    connect(clearTags, &QToolButton::clicked, this, [this]() {
        mSelectTagsComboBox->setSelectedTags({});
    });

    mTextAutoGenerateHistoryListView->setObjectName("mTextAutoGenerateHistoryListView"_L1);
    mainLayout->addWidget(mTextAutoGenerateHistoryListView);

    connect(mSearchLineEdit, &QLineEdit::textChanged, mTextAutoGenerateHistoryListView, &TextAutoGenerateHistoryListView::slotSearchTextChanged);
    connect(mSelectTagsComboBox,
            &TextAutoGenerateSelectTagsComboBox::selectedTagsChanged,
            mTextAutoGenerateHistoryListView,
            &TextAutoGenerateHistoryListView::slotFilterTagsChanged);

    if (mManager) {
        auto tagsModel = mManager->textAutoGenerateTagsManager()->textAutoGenerateTagsModel();
        connect(tagsModel, &QAbstractItemModel::modelReset, this, &TextAutoGenerateHistoryWidget::updateTags);
        connect(tagsModel, &QAbstractItemModel::rowsInserted, this, &TextAutoGenerateHistoryWidget::updateTags);
        connect(tagsModel, &QAbstractItemModel::rowsRemoved, this, &TextAutoGenerateHistoryWidget::updateTags);
        connect(tagsModel, &QAbstractItemModel::dataChanged, this, &TextAutoGenerateHistoryWidget::updateTags);
    }
    updateTags();
    connect(mTextAutoGenerateHistoryListView, &TextAutoGenerateHistoryListView::switchToChat, this, &TextAutoGenerateHistoryWidget::switchToChat);

    auto searchChatAction = new QAction(i18nc("@action", "Search Chat"), this);
    searchChatAction->setShortcut(shortcut);
    connect(searchChatAction, &QAction::triggered, this, [this]() {
        mSearchLineEdit->setFocus();
    });
    addAction(searchChatAction);

    auto previousChatAction = new QAction(i18nc("@action", "Previous Chat"), this);
    previousChatAction->setShortcut(Qt::CTRL | Qt::Key_Up);
    connect(previousChatAction, &QAction::triggered, this, [this]() {
        mTextAutoGenerateHistoryListView->selectNextChat(TextAutoGenerateHistoryListView::Direction::Up);
        mSearchLineEdit->clear();
    });
    addAction(previousChatAction);

    auto nextChatAction = new QAction(i18nc("@action", "Next Chat"), this);
    nextChatAction->setShortcut(Qt::CTRL | Qt::Key_Down);
    connect(nextChatAction, &QAction::triggered, this, [this]() {
        mTextAutoGenerateHistoryListView->selectNextChat(TextAutoGenerateHistoryListView::Direction::Down);
        mSearchLineEdit->clear();
    });
    addAction(nextChatAction);
}

TextAutoGenerateHistoryWidget::~TextAutoGenerateHistoryWidget() = default;

void TextAutoGenerateHistoryWidget::updateTags()
{
    const QList<TextAutoGenerateTag> tags = mManager ? mManager->textAutoGenerateTagsManager()->tags() : QList<TextAutoGenerateTag>{};
    // A removed tag must not keep filtering the history: only the tags which still exist are
    // selected again.
    const QList<QByteArray> previousSelection = mSelectTagsComboBox->selectedTags();
    mSelectTagsComboBox->setTags(tags);
    mSelectTagsComboBox->setSelectedTags(previousSelection);
    mSelectTagsComboBox->setVisible(!tags.isEmpty());
}

#include "moc_textautogeneratehistorywidget.cpp"
