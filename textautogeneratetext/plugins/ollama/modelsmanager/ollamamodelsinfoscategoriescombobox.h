/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QComboBox>

class OllamaModelsInfosCategoriesComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit OllamaModelsInfosCategoriesComboBox(QWidget *parent = nullptr);
    ~OllamaModelsInfosCategoriesComboBox() override;
};
