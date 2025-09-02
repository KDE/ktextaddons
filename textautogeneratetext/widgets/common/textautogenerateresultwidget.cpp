/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateresultwidget.h"
#include <qscrollbar.h>
using namespace Qt::Literals::StringLiterals;

#include "widgets/view/textautogeneratelistview.h"

#include <QVBoxLayout>

using namespace TextAutoGenerateText;
TextAutoGenerateResultWidget::TextAutoGenerateResultWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mTextAutoGenerateListView(new TextAutoGenerateListView(manager, this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});

    mTextAutoGenerateListView->setObjectName(u"mTextAutoGenerateListView"_s);
    mainLayout->addWidget(mTextAutoGenerateListView);
    connect(mTextAutoGenerateListView, &TextAutoGenerateListView::editMessageRequested, this, &TextAutoGenerateResultWidget::editMessageRequested);
    connect(mTextAutoGenerateListView, &TextAutoGenerateListView::cancelRequested, this, &TextAutoGenerateResultWidget::cancelRequested);
    connect(mTextAutoGenerateListView, &TextAutoGenerateListView::refreshAnswerRequested, this, &TextAutoGenerateResultWidget::refreshAnswerRequested);
}

TextAutoGenerateResultWidget::~TextAutoGenerateResultWidget() = default;

void TextAutoGenerateResultWidget::handleKeyPressEvent(QKeyEvent *ev)
{
    mTextAutoGenerateListView->handleKeyPressEvent(ev);
}

void TextAutoGenerateResultWidget::editingFinished(const QByteArray &uuid)
{
    mTextAutoGenerateListView->editingFinished(uuid);
}

int TextAutoGenerateResultWidget::scrollbarPosition() const
{
    return mTextAutoGenerateListView->verticalScrollBar()->value();
}

void TextAutoGenerateResultWidget::setScrollbarPosition(int position)
{
    mTextAutoGenerateListView->verticalScrollBar()->setValue(position);
}

void TextAutoGenerateResultWidget::scrollToBottom()
{
    mTextAutoGenerateListView->verticalScrollBar()->setValue(mTextAutoGenerateListView->verticalScrollBar()->maximum());
}

#include "moc_textautogenerateresultwidget.cpp"
