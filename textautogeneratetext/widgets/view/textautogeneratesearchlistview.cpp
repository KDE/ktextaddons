/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratesearchlistview.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratesearchmessagesmodel.h"
#include "textautogeneratesearchlistviewdelegate.h"

using namespace TextAutoGenerateText;
TextAutoGenerateSearchListView::TextAutoGenerateSearchListView(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent)
    : TextAutoGenerateBaseListView(manager, parent)
    , mModel(new TextAutoGenerateSearchMessagesModel(this))
{
    auto delegate = new TextAutoGenerateSearchListViewDelegate(this);
    connect(delegate, &TextAutoGenerateSearchListViewDelegate::goToMessage, this, &TextAutoGenerateSearchListView::slotGoToMessage);
    mDelegate = delegate;
    setItemDelegate(mDelegate);
    setModel(mModel);
}

TextAutoGenerateSearchListView::~TextAutoGenerateSearchListView() = default;

void TextAutoGenerateSearchListView::setSearchMessages(const QList<TextAutoGenerateSearchMessage> &msgs)
{
    mModel->setSearchMessages(msgs);
}

void TextAutoGenerateSearchListView::slotGoToMessage(const QUrl &link)
{
    // TODO
}

#include "moc_textautogeneratesearchlistview.cpp"
