/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateresultwidget.h"
#include "view/textautogeneratelistview.h"

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
    connect(mTextAutogenerateListView, &TextAutogenerateListView::editMessage, this, &TextAutogenerateResultWidget::editMessage);
    connect(this, &TextAutogenerateResultWidget::goToDiscussion, mTextAutogenerateListView, &TextAutogenerateListView::slotGoToDiscussion);
    connect(mTextAutogenerateListView, &TextAutogenerateListView::cancelRequest, this, &TextAutogenerateResultWidget::cancelRequest);
}

TextAutogenerateResultWidget::~TextAutogenerateResultWidget() = default;

void TextAutogenerateResultWidget::handleKeyPressEvent(QKeyEvent *ev)
{
    mTextAutogenerateListView->handleKeyPressEvent(ev);
}

void TextAutogenerateResultWidget::editingFinished(const QByteArray &uuid)
{
    mTextAutogenerateListView->editingFinished(uuid);
}
#include "moc_textautogenerateresultwidget.cpp"
