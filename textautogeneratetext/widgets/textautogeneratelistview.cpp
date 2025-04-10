/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratelistview.h"
#include "core/textautogeneratechatmodel.h"
#include "core/textautogeneratemanager.h"
#include "textautogeneratelistviewdelegate.h"

using namespace TextAutogenerateText;
TextAutogenerateListView::TextAutogenerateListView(QWidget *parent)
    : QListView(parent)
{
    setItemDelegate(new TextAutogenerateListViewDelegate(this));
    setModel(TextAutogenerateManager::self()->textAutoGenerateChatModel());
}

TextAutogenerateListView::~TextAutogenerateListView() = default;

void TextAutogenerateListView::setMessages(const QList<TextAutoGenerateMessage> &msg)
{
    TextAutogenerateManager::self()->textAutoGenerateChatModel()->setMessages(msg);
}

#include "moc_textautogeneratelistview.cpp"
