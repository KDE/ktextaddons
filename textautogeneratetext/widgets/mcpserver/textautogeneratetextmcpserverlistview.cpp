/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextmcpserverlistview.h"

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
TextAutoGenerateTextMcpServerListView::TextAutoGenerateTextMcpServerListView(QWidget *parent)
    : QListView(parent)
{
}

TextAutoGenerateTextMcpServerListView::~TextAutoGenerateTextMcpServerListView() = default;

#include "moc_textautogeneratetextmcpserverlistview.cpp"
