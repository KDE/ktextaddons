/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "ollamamodelinfo.h"
#include "textautogenerateollama_private_export.h"
#include <QComboBox>
class OllamaModelCategoriesModel;
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelsInfosCategoriesComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit OllamaModelsInfosCategoriesComboBox(QWidget *parent = nullptr);
    ~OllamaModelsInfosCategoriesComboBox() override;

    [[nodiscard]] QList<OllamaModelInfo::Category> categories() const;
Q_SIGNALS:
    void categoriesChanged();

private:
    OllamaModelCategoriesModel *const mModel;
};
