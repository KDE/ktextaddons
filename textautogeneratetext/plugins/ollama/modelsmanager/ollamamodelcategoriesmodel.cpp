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
    const QList<TextAutoGenerateText::TextAutoGenerateManager::Category> cat{
        TextAutoGenerateText::TextAutoGenerateManager::Category::Tools,
        TextAutoGenerateText::TextAutoGenerateManager::Category::Small,
        TextAutoGenerateText::TextAutoGenerateManager::Category::Medium,
        TextAutoGenerateText::TextAutoGenerateManager::Category::Big,
        TextAutoGenerateText::TextAutoGenerateManager::Category::Huge,
        TextAutoGenerateText::TextAutoGenerateManager::Category::Multilingual,
        TextAutoGenerateText::TextAutoGenerateManager::Category::Code,
        TextAutoGenerateText::TextAutoGenerateManager::Category::Math,
        TextAutoGenerateText::TextAutoGenerateManager::Category::Vision,
        TextAutoGenerateText::TextAutoGenerateManager::Category::Embedding,
        TextAutoGenerateText::TextAutoGenerateManager::Category::Reasoning,
    };
    mCategories.reserve(cat.count());

    for (const auto c : cat) {
        mCategories.append(CategoryInfo{
            .identifier = c,
            .name = TextAutoGenerateText::TextAutoGenerateManager::convertCategoryToI18n(c),
        });
    }
    auto item = new QStandardItem(i18n("Categories"));
    item->setSelectable(false);
    appendRow(item);
    for (const CategoryInfo &info : std::as_const(mCategories)) {
        createItem(info.name, info.identifier);
    }
}

void OllamaModelCategoriesModel::createItem(const QString &displayStr, TextAutoGenerateText::TextAutoGenerateManager::Category identifier)
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

QList<TextAutoGenerateText::TextAutoGenerateManager::Category> OllamaModelCategoriesModel::categoriesSelected() const
{
    QList<TextAutoGenerateText::TextAutoGenerateManager::Category> categoriesList;
    const int rowCountNb = rowCount();
    // First one is not a message type
    for (int i = 0; i < rowCountNb; i++) {
        QStandardItem *itemModel = item(i);
        if (itemModel) {
            if (itemModel->isCheckable() && itemModel->checkState() == Qt::Checked) {
                categoriesList.append(itemModel->data(Identifier).value<TextAutoGenerateText::TextAutoGenerateManager::Category>());
            }
        }
    }
    return categoriesList;
}

#include "moc_ollamamodelcategoriesmodel.cpp"
