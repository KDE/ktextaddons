/*
   SPDX-FileCopyrightText: 2024-2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#include "ollamamodelcategoriesmodel.h"
#include <KLocalizedString>

OllamaModelCategoriesModel::OllamaModelCategoriesModel(QObject *parent)
    : QStandardItemModel(parent)
{
    fillCategories();
}

OllamaModelCategoriesModel::~OllamaModelCategoriesModel() = default;

void OllamaModelCategoriesModel::fillCategories()
{
    const QList<OllamaModelAvailableInfo::Category> cat{
        OllamaModelAvailableInfo::Category::Tools,
        OllamaModelAvailableInfo::Category::Small,
        OllamaModelAvailableInfo::Category::Medium,
        OllamaModelAvailableInfo::Category::Big,
        OllamaModelAvailableInfo::Category::Huge,
        OllamaModelAvailableInfo::Category::Multilingual,
        OllamaModelAvailableInfo::Category::Code,
        OllamaModelAvailableInfo::Category::Math,
        OllamaModelAvailableInfo::Category::Vision,
        OllamaModelAvailableInfo::Category::Embedding,
        OllamaModelAvailableInfo::Category::Reasoning,
    };
    mCategories.reserve(cat.count());

    for (const auto c : cat) {
        mCategories.append(CategoryInfo{
            .identifier = c,
            .name = OllamaModelAvailableInfo::convertCategoryToI18n(c),
        });
    }
    auto item = new QStandardItem(i18n("Categories"));
    item->setSelectable(false);
    appendRow(item);
    for (const CategoryInfo &info : mCategories) {
        createItem(info.name, info.identifier);
    }
}

void OllamaModelCategoriesModel::createItem(const QString &displayStr, OllamaModelAvailableInfo::Category identifier)
{
    auto item = new QStandardItem(displayStr);
    item->setFlags(Qt::ItemIsUserCheckable | Qt::ItemIsEnabled);
    item->setData(QVariant::fromValue(identifier), Identifier);
    item->setData(Qt::Unchecked, Qt::CheckStateRole);
    item->setToolTip(displayStr);
    appendRow(item);
}

QList<OllamaModelCategoriesModel::CategoryInfo> OllamaModelCategoriesModel::categories() const
{
    return mCategories;
}

QList<OllamaModelAvailableInfo::Category> OllamaModelCategoriesModel::categoriesSelected() const
{
    QList<OllamaModelAvailableInfo::Category> categories;
    const int rowCountNb = rowCount();
    // First one is not a message type
    for (int i = 0; i < rowCountNb; i++) {
        QStandardItem *itemModel = item(i);
        if (itemModel) {
            if (itemModel->isCheckable() && itemModel->checkState() == Qt::Checked) {
                categories.append(itemModel->data(Identifier).value<OllamaModelAvailableInfo::Category>());
            }
        }
    }
    return categories;
}

#include "moc_ollamamodelcategoriesmodel.cpp"
