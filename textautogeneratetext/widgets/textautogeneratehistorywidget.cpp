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

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutogenerateHistoryWidget::TextAutogenerateHistoryWidget(QWidget *parent)
    : QWidget{parent}
    , mTextAutogenerateHistoryListView(new TextAutogenerateHistoryListView(this))
    , mSearchLineEdit(new QLineEdit(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});

    mSearchLineEdit->setObjectName("mSearchLineEdit"_L1);
    mSearchLineEdit->setClearButtonEnabled(true);
    mSearchLineEdit->addAction(QIcon::fromTheme(QStringLiteral("view-filter")), QLineEdit::LeadingPosition);
    mSearchLineEdit->setPlaceholderText(i18nc("@info:placeholder", "Search…"));
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);
    mainLayout->addWidget(mSearchLineEdit);

    mTextAutogenerateHistoryListView->setObjectName("mTextAutogenerateHistoryListView"_L1);
    mainLayout->addWidget(mTextAutogenerateHistoryListView);

    connect(mSearchLineEdit, &QLineEdit::textChanged, mTextAutogenerateHistoryListView, &TextAutogenerateHistoryListView::slotSearchTextChanged);
    connect(mTextAutogenerateHistoryListView, &TextAutogenerateHistoryListView::goToDiscussion, this, &TextAutogenerateHistoryWidget::goToDiscussion);
}

TextAutogenerateHistoryWidget::~TextAutogenerateHistoryWidget() = default;

#include "moc_textautogeneratehistorywidget.cpp"
