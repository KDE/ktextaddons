/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamamodelinfossortproxymodel.h"

OllamaModelInfosSortProxyModel::OllamaModelInfosSortProxyModel(QObject *parent)
    : QSortFilterProxyModel{parent}
{
    setFilterCaseSensitivity(Qt::CaseInsensitive);
}

OllamaModelInfosSortProxyModel::~OllamaModelInfosSortProxyModel() = default;

OllamaModelInfo::Categories OllamaModelInfosSortProxyModel::categories() const
{
    return mCategories;
}

void OllamaModelInfosSortProxyModel::setCategories(const OllamaModelInfo::Categories &newCategories)
{
    if (mCategories != newCategories) {
        mCategories = newCategories;
        invalidateFilter();
    }
}

#include "moc_ollamamodelinfossortproxymodel.cpp"
