/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancesortfilterproxymodel.h"
#include "textautogeneratetextinstancemodel.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextInstanceSortFilterProxyModel::TextAutoGenerateTextInstanceSortFilterProxyModel(QObject *parent)
    : TextAddonsWidgets::SortFilterProxyModelBase{parent}
{
    setSortCaseSensitivity(Qt::CaseInsensitive);
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setFilterRole(TextAutoGenerateTextInstanceModel::Name);
    sort(0);
}

TextAutoGenerateTextInstanceSortFilterProxyModel::~TextAutoGenerateTextInstanceSortFilterProxyModel() = default;

bool TextAutoGenerateTextInstanceSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (mFilterString.trimmed().isEmpty()) {
        return true;
    }
    const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
    const QString instanceName = sourceIndex.data(TextAutoGenerateTextInstanceModel::Name).toString();
    const QString pluginName = sourceIndex.data(TextAutoGenerateTextInstanceModel::PluginName).toString();
    if (contains(pluginName) || contains(instanceName)) {
        return true;
    }
    return false;
}

#include "moc_textautogeneratetextinstancesortfilterproxymodel.cpp"
