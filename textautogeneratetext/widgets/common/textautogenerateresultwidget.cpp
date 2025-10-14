/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateresultwidget.h"
#include <QScrollBar>

#include "widgets/view/textautogeneratelistview.h"
#include <TextAddonsWidgets/QuickSearchBarWidget>

#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateResultWidget::TextAutoGenerateResultWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mTextAutoGenerateListView(new TextAutoGenerateListView(manager, this))
    , mQuickSearchBarWidget(new TextAddonsWidgets::QuickSearchBarWidget(this))
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
            &TextAddonsWidgets::QuickSearchBarWidget::searchTextRequested,
            mTextAutoGenerateListView,
            &TextAutoGenerateListView::setSearchText);

    connect(mQuickSearchBarWidget,
            &TextAddonsWidgets::QuickSearchBarWidget::closeSearchBarRequested,
            this,
            &TextAutoGenerateResultWidget::closeSearchBarRequested);

    connect(mQuickSearchBarWidget, &TextAddonsWidgets::QuickSearchBarWidget::findPrev, this, &TextAutoGenerateResultWidget::slotFindPrev);

    connect(mQuickSearchBarWidget, &TextAddonsWidgets::QuickSearchBarWidget::findNext, this, &TextAutoGenerateResultWidget::slotFindNext);
}

TextAutoGenerateResultWidget::~TextAutoGenerateResultWidget() = default;

void TextAutoGenerateResultWidget::slotFindPrev()
{
    mTextAutoGenerateListView->slotFindPrev();
    qDebug() << " void TextAutoGenerateResultWidget::slotFindPrev()";
}

void TextAutoGenerateResultWidget::slotFindNext()
{
    mTextAutoGenerateListView->slotFindNext();
    qDebug() << " void TextAutoGenerateResultWidget::slotFindNext()";
}

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

void TextAutoGenerateResultWidget::quickSearchText(bool enabled)
{
    if (enabled) {
        mQuickSearchBarWidget->slideIn();
    } else {
        mQuickSearchBarWidget->slideOut();
    }
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
