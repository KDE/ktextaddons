/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratehistorywidget.h"
#include "widgets/textautogeneratehistorylistview.h"
#include <QVBoxLayout>

using namespace TextAutogenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutogenerateHistoryWidget::TextAutogenerateHistoryWidget(QWidget *parent)
    : QWidget{parent}
    , mTextAutogenerateHistoryListView(new TextAutogenerateHistoryListView(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName("mainLayout"_L1);
    mainLayout->setContentsMargins({});

    // TODO add search lineedit
    // TODO add model

    mTextAutogenerateHistoryListView->setObjectName("mTextAutogenerateHistoryListView"_L1);
    mainLayout->addWidget(mTextAutogenerateHistoryListView);
}

TextAutogenerateHistoryWidget::~TextAutogenerateHistoryWidget() = default;

#include "moc_textautogeneratehistorywidget.cpp"
