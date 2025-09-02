/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratehistorywidget.h"
#include "widgets/view/textautogeneratehistorylistview.h"
#include <KLineEditEventHandler>
#include <KLocalizedString>
#include <QLineEdit>
#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateHistoryWidget::TextAutoGenerateHistoryWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mTextAutoGenerateHistoryListView(new TextAutoGenerateHistoryListView(manager, this))
    , mSearchLineEdit(new QLineEdit(this))
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

    mTextAutoGenerateHistoryListView->setObjectName("mTextAutoGenerateHistoryListView"_L1);
    mainLayout->addWidget(mTextAutoGenerateHistoryListView);

    connect(mSearchLineEdit, &QLineEdit::textChanged, mTextAutoGenerateHistoryListView, &TextAutoGenerateHistoryListView::slotSearchTextChanged);
    connect(mTextAutoGenerateHistoryListView, &TextAutoGenerateHistoryListView::switchToChat, this, &TextAutoGenerateHistoryWidget::switchToChat);

    auto searchRoomAction = new QAction(i18nc("@action", "Search Channels"), this);
    searchRoomAction->setShortcut(shortcut);
    connect(searchRoomAction, &QAction::triggered, this, [this]() {
        mSearchLineEdit->setFocus();
    });
    addAction(searchRoomAction);

    auto previousRoomAction = new QAction(i18nc("@action", "Previous Chat"), this);
    previousRoomAction->setShortcut(Qt::CTRL | Qt::Key_Up);
    connect(previousRoomAction, &QAction::triggered, this, [this]() {
        mTextAutoGenerateHistoryListView->selectNextChat(TextAutoGenerateHistoryListView::Direction::Up);
        mSearchLineEdit->clear();
    });
    addAction(previousRoomAction);

    auto nextRoomAction = new QAction(i18nc("@action", "Next Chat"), this);
    nextRoomAction->setShortcut(Qt::CTRL | Qt::Key_Down);
    connect(nextRoomAction, &QAction::triggered, this, [this]() {
        mTextAutoGenerateHistoryListView->selectNextChat(TextAutoGenerateHistoryListView::Direction::Down);
        mSearchLineEdit->clear();
    });
    addAction(nextRoomAction);
}

TextAutoGenerateHistoryWidget::~TextAutoGenerateHistoryWidget() = default;

#include "moc_textautogeneratehistorywidget.cpp"
