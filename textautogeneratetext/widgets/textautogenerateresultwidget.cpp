/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateresultwidget.h"
#include "textautogeneratelistview.h"

#include <QVBoxLayout>

using namespace TextAutogenerateText;
TextAutogenerateResultWidget::TextAutogenerateResultWidget(QWidget *parent)
    : QWidget{parent}
    , mTextAutogenerateListView(new TextAutogenerateListView(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(QStringLiteral("mainLayout"));
    mainLayout->setContentsMargins(QMargins{});

    mTextAutogenerateListView->setObjectName(QStringLiteral("mTextAutogenerateListView"));
    mainLayout->addWidget(mTextAutogenerateListView);
}

TextAutogenerateResultWidget::~TextAutogenerateResultWidget() = default;

#include "moc_textautogenerateresultwidget.cpp"
