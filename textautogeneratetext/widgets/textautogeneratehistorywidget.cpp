/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratehistorywidget.h"
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
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});

    mSearchLineEdit->setObjectName("mSearchLineEdit"_L1);
    mSearchLineEdit->setClearButtonEnabled(true);
    KLineEditEventHandler::catchReturnKey(mSearchLineEdit);
    mainLayout->addWidget(mSearchLineEdit);
    // TODO add model

    mTextAutogenerateHistoryListView->setObjectName("mTextAutogenerateHistoryListView"_L1);
    mainLayout->addWidget(mTextAutogenerateHistoryListView);
}

TextAutogenerateHistoryWidget::~TextAutogenerateHistoryWidget() = default;

#include "moc_textautogeneratehistorywidget.cpp"
