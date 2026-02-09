/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamacommonmodelsinfoscategoriescombobox.h"
#include "ollamacommonmodelcategoriesmodel.h"
OllamaCommonModelsInfosCategoriesComboBox::OllamaCommonModelsInfosCategoriesComboBox(QWidget *parent)
    : QComboBox(parent)
    , mModel(new OllamaCommonModelCategoriesModel(this))
{
    setModel(mModel);
    connect(mModel, &OllamaCommonModelCategoriesModel::itemChanged, this, &OllamaCommonModelsInfosCategoriesComboBox::categoriesChanged);
    setSizeAdjustPolicy(QComboBox::AdjustToContents);
}

OllamaCommonModelsInfosCategoriesComboBox::~OllamaCommonModelsInfosCategoriesComboBox() = default;

QList<TextAutoGenerateText::TextAutoGenerateManager::Category> OllamaCommonModelsInfosCategoriesComboBox::categories() const
{
    return mModel->categoriesSelected();
}

#include "moc_ollamacommonmodelsinfoscategoriescombobox.cpp"
