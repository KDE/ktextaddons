/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancesmanagerlistview.h"
#include "core/models/textautogeneratetextinstancemodel.h"
#include <QSortFilterProxyModel>
using namespace TextAutoGenerateText;
TextAutoGenerateTextInstancesManagerListView::TextAutoGenerateTextInstancesManagerListView(QWidget *parent)
    : QListView(parent)
    , mModel(new TextAutoGenerateTextInstanceModel(this))
    , mSortFilterProxyModel(new QSortFilterProxyModel(this))
{
    setDragEnabled(false);
    mSortFilterProxyModel->setSourceModel(mModel);
    setModel(mSortFilterProxyModel);
}

TextAutoGenerateTextInstancesManagerListView::~TextAutoGenerateTextInstancesManagerListView() = default;

void TextAutoGenerateTextInstancesManagerListView::slotSearchChanged(const QString &str)
{
    mSortFilterProxyModel->setFilterFixedString(str);
}

#include "moc_textautogeneratetextinstancesmanagerlistview.cpp"
