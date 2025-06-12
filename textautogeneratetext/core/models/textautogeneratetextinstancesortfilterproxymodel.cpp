/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstancesortfilterproxymodel.h"
#include "textautogeneratetextinstancemodel.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextInstanceSortFilterProxyModel::TextAutoGenerateTextInstanceSortFilterProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
}

TextAutoGenerateTextInstanceSortFilterProxyModel::~TextAutoGenerateTextInstanceSortFilterProxyModel() = default;

bool TextAutoGenerateTextInstanceSortFilterProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    if (mSearchText.trimmed().isEmpty()) {
        return true;
    }
    const QModelIndex sourceIndex = sourceModel()->index(source_row, 0, source_parent);
    const QString instanceName = sourceIndex.data(TextAutoGenerateTextInstanceModel::Name).toString();
    const QString pluginName = sourceIndex.data(TextAutoGenerateTextInstanceModel::PluginName).toString();
    if (pluginName.contains(mSearchText, Qt::CaseInsensitive) || instanceName.contains(mSearchText, Qt::CaseInsensitive)) {
        return true;
    }
    return false;
}

QString TextAutoGenerateTextInstanceSortFilterProxyModel::searchText() const
{
    return mSearchText;
}

void TextAutoGenerateTextInstanceSortFilterProxyModel::setSearchText(const QString &newSearchText)
{
    if (mSearchText != newSearchText) {
        mSearchText = newSearchText;
        invalidateFilter();
    }
}

#include "moc_textautogeneratetextinstancesortfilterproxymodel.cpp"
