/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "ollamamodelinfo.h"
#include "textautogenerateollama_private_export.h"
#include <QWidget>
class QLineEdit;
class OllamaModelsInfosCategoriesComboBox;
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelSearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelSearchWidget(QWidget *parent = nullptr);
    ~OllamaModelSearchWidget() override;

Q_SIGNALS:
    void searchText(const QString &str);
    void categoriesChanged(OllamaModelInfo::Categories categories);

private:
    QLineEdit *const mSearchLineEdit;
    OllamaModelsInfosCategoriesComboBox *const mCategoriesComboBox;
};
