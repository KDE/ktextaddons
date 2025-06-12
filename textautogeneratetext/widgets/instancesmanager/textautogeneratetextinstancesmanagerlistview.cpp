/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancesmanagerlistview.h"
#include "core/models/textautogeneratetextinstancemodel.h"
#include "core/textautogeneratetextinstancesmanager.h"
#include "textautogeneratetextinstancesmanagerlistviewdelegate.h"
#include <QSortFilterProxyModel>
#include <TextAutoGenerateText/TextAutoGenerateManager>
using namespace TextAutoGenerateText;
TextAutoGenerateTextInstancesManagerListView::TextAutoGenerateTextInstancesManagerListView(TextAutoGenerateText::TextAutoGenerateManager *manager,
                                                                                           QWidget *parent)
    : QListView(parent)
    , mSortFilterProxyModel(new QSortFilterProxyModel(this))
    , mTextAutoGenerateManager(manager)
{
    setItemDelegate(new TextAutoGenerateTextInstancesManagerListViewDelegate(this));
    setDragEnabled(false);
    if (mTextAutoGenerateManager) {
        mSortFilterProxyModel->setSourceModel(mTextAutoGenerateManager->textAutoGenerateTextInstancesManager()->textAutoGenerateTextInstanceModel());
    }
    setModel(mSortFilterProxyModel);
}

TextAutoGenerateTextInstancesManagerListView::~TextAutoGenerateTextInstancesManagerListView() = default;

void TextAutoGenerateTextInstancesManagerListView::slotSearchChanged(const QString &str)
{
    mSortFilterProxyModel->setFilterFixedString(str);
}

#include "moc_textautogeneratetextinstancesmanagerlistview.cpp"
