/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamamodelavailableinfossortproxymodel.h"
#include "ollamamodelavailableinfosmodel.h"

OllamaModelAvailableInfosSortProxyModel::OllamaModelAvailableInfosSortProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
}

OllamaModelAvailableInfosSortProxyModel::~OllamaModelAvailableInfosSortProxyModel() = default;

QList<OllamaModelAvailableInfo::Category> OllamaModelAvailableInfosSortProxyModel::categories() const
{
    return mCategories;
}

void OllamaModelAvailableInfosSortProxyModel::setCategories(const QList<OllamaModelAvailableInfo::Category> &newCategories)
{
    if (mCategories != newCategories) {
        mCategories = newCategories;
        invalidateFilter();
    }
}

bool OllamaModelAvailableInfosSortProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    const QModelIndex modelIndex = sourceModel()->index(source_row, 0, source_parent);
    if (!mCategories.isEmpty()) {
        const OllamaModelAvailableInfo::Categories categories =
            modelIndex.data(OllamaModelAvailableInfosModel::Categories).value<OllamaModelAvailableInfo::Categories>();
        if (categories == OllamaModelAvailableInfo::Category::Unknown) {
            return true;
        }
        for (const auto c : std::as_const(mCategories)) {
            if (!(categories & c)) {
                return false;
            }
        }
    }

    return QSortFilterProxyModel::filterAcceptsRow(source_row, source_parent);
}

#include "moc_ollamamodelavailableinfossortproxymodel.cpp"
