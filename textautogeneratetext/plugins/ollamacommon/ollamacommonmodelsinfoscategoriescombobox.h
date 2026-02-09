/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollamacommon_export.h"
#include <QComboBox>
#include <TextAutoGenerateText/TextAutoGenerateManager>
class OllamaCommonModelCategoriesModel;
class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonModelsInfosCategoriesComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit OllamaCommonModelsInfosCategoriesComboBox(QWidget *parent = nullptr);
    ~OllamaCommonModelsInfosCategoriesComboBox() override;

    [[nodiscard]] QList<TextAutoGenerateText::TextAutoGenerateManager::Category> categories() const;
Q_SIGNALS:
    void categoriesChanged();

private:
    OllamaCommonModelCategoriesModel *const mModel;
};
