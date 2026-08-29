/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextpromptsortfilterproxymodel.h"
#include "textautogeneratetextpromptmodel.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextPromptSortFilterProxyModel::TextAutoGenerateTextPromptSortFilterProxyModel(QObject *parent)
    : TextAddonsWidgets::SortFilterProxyModelBase{parent}
{
    setSortCaseSensitivity(Qt::CaseInsensitive);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setFilterRole(TextAutoGenerateTextPromptModel::Name);
    sort(0);
}

TextAutoGenerateTextPromptSortFilterProxyModel::~TextAutoGenerateTextPromptSortFilterProxyModel() = default;

bool TextAutoGenerateTextPromptSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (mFilterString.trimmed().isEmpty()) {
        return true;
    }
    const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
    if (const QString instanceName = sourceIndex.data(TextAutoGenerateTextPromptModel::Name).toString(); contains(instanceName)) {
        return true;
    }
    return false;
}

#include "moc_textautogeneratetextpromptsortfilterproxymodel.cpp"
