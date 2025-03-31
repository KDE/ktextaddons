/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratehistorywidget.h"
#include "core/textautogeneratehistorymodel.h"
#include "core/textautogeneratehistorysortfilterproxymodel.h"
#include "widgets/textautogeneratehistorylistview.h"
#include <KLineEditEventHandler>
#include <QLineEdit>
#include <QVBoxLayout>

using namespace TextAutogenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutogenerateHistoryWidget::TextAutogenerateHistoryWidget(QWidget *parent)
    : QWidget{parent}
    , mTextAutogenerateHistoryListView(new TextAutogenerateHistoryListView(this))
    , mSearchLineEdit(new QLineEdit(this))
    , mHistoryProxyModel(new TextAutoGenerateHistorySortFilterProxyModel(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});

    mSearchLineEdit->setObjectName("mSearchLineEdit"_L1);
    mSearchLineEdit->setClearButtonEnabled(true);
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);
    mainLayout->addWidget(mSearchLineEdit);

    auto historyModel = new TextAutoGenerateHistoryModel(this);

    mHistoryProxyModel->setSourceModel(historyModel);
    mTextAutogenerateHistoryListView->setModel(mHistoryProxyModel);

    mTextAutogenerateHistoryListView->setObjectName("mTextAutogenerateHistoryListView"_L1);
    mainLayout->addWidget(mTextAutogenerateHistoryListView);

    connect(mSearchLineEdit, &QLineEdit::textChanged, this, &TextAutogenerateHistoryWidget::slotSearchTextChanged);
}

TextAutogenerateHistoryWidget::~TextAutogenerateHistoryWidget() = default;

void TextAutogenerateHistoryWidget::slotSearchTextChanged(const QString &str)
{
    // TODO change listview
}

#include "moc_textautogeneratehistorywidget.cpp"
