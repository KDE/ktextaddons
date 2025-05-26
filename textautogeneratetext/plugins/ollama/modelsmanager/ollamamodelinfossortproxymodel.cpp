/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamamodelinfossortproxymodel.h"
#include "ollamamodelavailableinfosmodel.h"

OllamaModelInfosSortProxyModel::OllamaModelInfosSortProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
}

OllamaModelInfosSortProxyModel::~OllamaModelInfosSortProxyModel() = default;

QList<OllamaModelAvailableInfo::Category> OllamaModelInfosSortProxyModel::categories() const
{
    return mCategories;
}

void OllamaModelInfosSortProxyModel::setCategories(const QList<OllamaModelAvailableInfo::Category> &newCategories)
{
    if (mCategories != newCategories) {
        mCategories = newCategories;
        invalidateFilter();
    }
}

bool OllamaModelInfosSortProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
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

#include "moc_ollamamodelinfossortproxymodel.cpp"
