/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateresultwidget.h"
#include <QScrollBar>

#include "widgets/view/textautogeneratelistview.h"
#include "widgets/view/textautogeneratequicksearchbarwidget.h"

#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateResultWidget::TextAutoGenerateResultWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mTextAutoGenerateListView(new TextAutoGenerateListView(manager, this))
    , mQuickSearchBarWidget(new TextAutoGenerateQuickSearchBarWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});

    mQuickSearchBarWidget->setObjectName(u"mQuickSearchBarWidget"_s);
    mainLayout->addWidget(mQuickSearchBarWidget);

    mTextAutoGenerateListView->setObjectName(u"mTextAutoGenerateListView"_s);
    mainLayout->addWidget(mTextAutoGenerateListView);
    connect(mTextAutoGenerateListView, &TextAutoGenerateListView::editMessageRequested, this, &TextAutoGenerateResultWidget::editMessageRequested);
    connect(mTextAutoGenerateListView, &TextAutoGenerateListView::cancelRequested, this, &TextAutoGenerateResultWidget::cancelRequested);
    connect(mTextAutoGenerateListView, &TextAutoGenerateListView::refreshAnswerRequested, this, &TextAutoGenerateResultWidget::refreshAnswerRequested);

    connect(mQuickSearchBarWidget,
            &TextAutoGenerateQuickSearchBarWidget::searchTextRequested,
            mTextAutoGenerateListView,
            &TextAutoGenerateListView::setSearchText);

    // REMOVE IT only for test
    mQuickSearchBarWidget->slideIn();
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

int TextAutoGenerateResultWidget::scrollbarPositionMaximum() const
{
    return mTextAutoGenerateListView->verticalScrollBar()->maximum();
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
