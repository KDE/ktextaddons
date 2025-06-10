/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancesmanagerlistview.h"
#include "core/models/textautogeneratetextinstancemodel.h"
using namespace TextAutoGenerateText;
TextAutoGenerateTextInstancesManagerListView::TextAutoGenerateTextInstancesManagerListView(QWidget *parent)
    : QListView(parent)
    , mModel(new TextAutoGenerateTextInstanceModel(this))
{
    setDragEnabled(false);
    setModel(mModel);
}

TextAutoGenerateTextInstancesManagerListView::~TextAutoGenerateTextInstancesManagerListView() = default;

void TextAutoGenerateTextInstancesManagerListView::slotSearchChanged(const QString &str)
{
    // TODO
}

#include "moc_textautogeneratetextinstancesmanagerlistview.cpp"
