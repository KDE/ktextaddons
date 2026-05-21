/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateresultwidget.h"
#include <QScrollBar>

#include "widgets/view/textautogeneratelistview.h"
#include <TextAddonsWidgets/OpenSavedFileFolderWidget>
#include <TextAddonsWidgets/QuickSearchBarWidget>

#include <QVBoxLayout>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
TextAutoGenerateResultWidget::TextAutoGenerateResultWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : QWidget{parent}
    , mTextAutoGenerateListView(new TextAutoGenerateListView(manager, this))
    , mQuickSearchBarWidget(new TextAddonsWidgets::QuickSearchBarWidget(this))
    , mOpenSavedFileFolderWidget(new TextAddonsWidgets::OpenSavedFileFolderWidget(this))
{
    auto mainLayout = new QVBoxLayout(this);
    mainLayout->setObjectName(u"mainLayout"_s);
    mainLayout->setContentsMargins(QMargins{});

    mQuickSearchBarWidget->setObjectName(u"mQuickSearchBarWidget"_s);
    mainLayout->addWidget(mQuickSearchBarWidget);

    mOpenSavedFileFolderWidget->setObjectName(u"mOpenSavedFileFolderWidget"_s);
    mainLayout->addWidget(mOpenSavedFileFolderWidget);

    mTextAutoGenerateListView->setObjectName(u"mTextAutoGenerateListView"_s);
    mainLayout->addWidget(mTextAutoGenerateListView);
    connect(mTextAutoGenerateListView, &TextAutoGenerateListView::editMessageRequested, this, &TextAutoGenerateResultWidget::editMessageRequested);
    connect(mTextAutoGenerateListView, &TextAutoGenerateListView::cancelRequested, this, &TextAutoGenerateResultWidget::cancelRequested);
    connect(mTextAutoGenerateListView, &TextAutoGenerateListView::refreshAnswerRequested, this, &TextAutoGenerateResultWidget::refreshAnswerRequested);
    connect(mTextAutoGenerateListView,
            &TextAutoGenerateListView::updateNextPreviousButtons,
            mQuickSearchBarWidget,
            &TextAddonsWidgets::QuickSearchBarWidget::updateButtons);

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

    if (manager) {
        connect(manager,
                &TextAutoGenerateText::TextAutoGenerateManager::currentChatIdChanged,
                mQuickSearchBarWidget,
                &TextAddonsWidgets::QuickSearchBarWidget::slideOut);
        connect(manager, &TextAutoGenerateText::TextAutoGenerateManager::numberOfSearchStringChanged, this, [this](int numberOfSearch) {
            if (numberOfSearch == 0) {
                mQuickSearchBarWidget->updateButtons(false, false);
            }
        });
        connect(manager,
                &TextAutoGenerateText::TextAutoGenerateManager::openSavedFileFolderDone,
                this,
                &TextAutoGenerateResultWidget::slotOpenSavedFileFolderDone);
    }
}

TextAutoGenerateResultWidget::~TextAutoGenerateResultWidget() = default;

void TextAutoGenerateResultWidget::slotOpenSavedFileFolderDone(const QList<QUrl> &urls, TextAutoGenerateText::TextAutoGenerateManager::FileType fileType)
{
    TextAddonsWidgets::OpenSavedFileFolderWidget::FileType openSavedFileType = TextAddonsWidgets::OpenSavedFileFolderWidget::FileType::Unknown;
    switch (fileType) {
    case TextAutoGenerateText::TextAutoGenerateManager::FileType::Unknown:
        openSavedFileType = TextAddonsWidgets::OpenSavedFileFolderWidget::FileType::Unknown;
        break;
    case TextAutoGenerateText::TextAutoGenerateManager::FileType::Attachment:
        openSavedFileType = TextAddonsWidgets::OpenSavedFileFolderWidget::FileType::Attachment;
        break;
    case TextAutoGenerateText::TextAutoGenerateManager::FileType::Pdf:
        openSavedFileType = TextAddonsWidgets::OpenSavedFileFolderWidget::FileType::Pdf;
        break;
    case TextAutoGenerateText::TextAutoGenerateManager::FileType::File:
        openSavedFileType = TextAddonsWidgets::OpenSavedFileFolderWidget::FileType::File;
        break;
    }
    mOpenSavedFileFolderWidget->setUrls(urls, openSavedFileType);
}

void TextAutoGenerateResultWidget::slotFindPrev()
{
    mTextAutoGenerateListView->slotFindPrev();
}

void TextAutoGenerateResultWidget::slotFindNext()
{
    mTextAutoGenerateListView->slotFindNext();
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
