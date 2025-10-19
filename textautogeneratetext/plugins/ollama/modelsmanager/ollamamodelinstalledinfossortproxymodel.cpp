/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamamodelinstalledinfossortproxymodel.h"
#include "ollamamodelinstalledinfosmodel.h"

OllamaModelInstalledInfosSortProxyModel::OllamaModelInstalledInfosSortProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
    setSortCaseSensitivity(Qt::CaseInsensitive);
}

OllamaModelInstalledInfosSortProxyModel::~OllamaModelInstalledInfosSortProxyModel() = default;

QList<TextAutoGenerateText::TextAutoGenerateManager::Category> OllamaModelInstalledInfosSortProxyModel::categories() const
{
    return mCategories;
}

void OllamaModelInstalledInfosSortProxyModel::setCategories(const QList<TextAutoGenerateText::TextAutoGenerateManager::Category> &newCategories)
{
    if (mCategories != newCategories) {
#if QT_VERSION >= QT_VERSION_CHECK(6, 10, 0)
        beginFilterChange();
#endif
        mCategories = newCategories;
#if QT_VERSION >= QT_VERSION_CHECK(6, 10, 0)
        endFilterChange(QSortFilterProxyModel::Direction::Rows);
#else
        invalidateFilter();
#endif
    }
}

bool OllamaModelInstalledInfosSortProxyModel::filterAcceptsRow(int source_row, const QModelIndex &source_parent) const
{
    const QModelIndex modelIndex = sourceModel()->index(source_row, 0, source_parent);
    if (!mCategories.isEmpty()) {
        const TextAutoGenerateText::TextAutoGenerateManager::Categories categories =
            modelIndex.data(OllamaModelInstalledInfosModel::Categories).value<TextAutoGenerateText::TextAutoGenerateManager::Categories>();
        if (categories == TextAutoGenerateText::TextAutoGenerateManager::Category::Unknown) {
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

#include "moc_ollamamodelinstalledinfossortproxymodel.cpp"
