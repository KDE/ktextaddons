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
    const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
    if (mInstanceFilter == TextAutoGenerateTextInstancesManager::InstanceFilter::LocalOnly
        && !sourceIndex.data(TextAutoGenerateTextInstanceModel::IsLocalServer).toBool()) {
        return false;
    }
    if (mFilterString.trimmed().isEmpty()) {
        return true;
    }
    const QString instanceName = sourceIndex.data(TextAutoGenerateTextInstanceModel::Name).toString();
    if (const QString pluginName = sourceIndex.data(TextAutoGenerateTextInstanceModel::PluginName).toString(); contains(pluginName) || contains(instanceName)) {
        return true;
    }
    return false;
}

TextAutoGenerateTextInstancesManager::InstanceFilter TextAutoGenerateTextInstanceSortFilterProxyModel::instanceFilter() const
{
    return mInstanceFilter;
}

void TextAutoGenerateTextInstanceSortFilterProxyModel::setInstanceFilter(TextAutoGenerateTextInstancesManager::InstanceFilter newInstanceFilter)
{
    if (mInstanceFilter != newInstanceFilter) {
        beginFilterChange();
        mInstanceFilter = newInstanceFilter;
        endFilterChange(QSortFilterProxyModel::Direction::Rows);
    }
}

#include "moc_textautogeneratetextinstancesortfilterproxymodel.cpp"
