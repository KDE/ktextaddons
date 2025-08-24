/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamamodelsinfoscategoriescombobox.h"
#include "ollamamodelcategoriesmodel.h"
OllamaModelsInfosCategoriesComboBox::OllamaModelsInfosCategoriesComboBox(QWidget *parent)
    : QComboBox(parent)
    , mModel(new OllamaModelCategoriesModel(this))
{
    setModel(mModel);
    connect(mModel, &OllamaModelCategoriesModel::itemChanged, this, &OllamaModelsInfosCategoriesComboBox::categoriesChanged);
    setSizeAdjustPolicy(QComboBox::AdjustToContents);
}

OllamaModelsInfosCategoriesComboBox::~OllamaModelsInfosCategoriesComboBox() = default;

QList<TextAutoGenerateText::TextAutoGenerateManager::Category> OllamaModelsInfosCategoriesComboBox::categories() const
{
    return mModel->categoriesSelected();
}

#include "moc_ollamamodelsinfoscategoriescombobox.cpp"
