/*
   SPDX-FileCopyrightText: 2024-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "ollamamodelcategoriesmodel.h"
#include <KLocalizedString>

OllamaModelCategoriesModel::OllamaModelCategoriesModel(QObject *parent)
    : QStandardItemModel(parent)
{
}

OllamaModelCategoriesModel::~OllamaModelCategoriesModel() = default;

void OllamaModelCategoriesModel::createItem(const QString &displayStr, const QString &identifier)
{
    auto item = new QStandardItem(displayStr);
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setData(identifier, Identifier);
    item->setData(Qt::Unchecked, Qt::CheckStateRole);
    item->setToolTip(displayStr);
    appendRow(item);
}

QList<OllamaModelCategoriesModel::CategoryInfo> OllamaModelCategoriesModel::appsCategories() const
{
    return mAppsCategories;
}

void OllamaModelCategoriesModel::setAppsCategories(const QList<CategoryInfo> &appsCategories)
{
    auto item = new QStandardItem(i18n("Categories"));
    item->setSelectable(false);
    appendRow(item);
    for (const CategoryInfo &info : appsCategories) {
        createItem(info.name, info.identifier);
    }
}

bool OllamaModelCategoriesModel::wasFilled() const
{
    return !mAppsCategories.isEmpty();
}

QStringList OllamaModelCategoriesModel::categoriesSelected() const
{
    QStringList lst;
    const int rowCountNb = rowCount();
    // First one is not a message type
    for (int i = 0; i < rowCountNb; i++) {
        QStandardItem *itemModel = item(i);
        if (itemModel) {
            if (itemModel->isCheckable() && itemModel->checkState() == Qt::Checked) {
                lst.append(itemModel->data(Qt::DisplayRole).toString());
            }
        }
    }
    return lst;
}

#include "moc_ollamamodelcategoriesmodel.cpp"
