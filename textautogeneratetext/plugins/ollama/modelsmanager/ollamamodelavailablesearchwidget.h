/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "ollamamodelavailableinfo.h"
#include "textautogenerateollama_private_export.h"
#include <QWidget>
class OllamaModelSearchLineEdit;
class OllamaModelsInfosCategoriesComboBox;
class QToolButton;
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelAvailableSearchWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelAvailableSearchWidget(QWidget *parent = nullptr);
    ~OllamaModelAvailableSearchWidget() override;

Q_SIGNALS:
    void searchText(const QString &str);
    void categoriesChanged(const QList<OllamaModelAvailableInfo::Category> &categories);
    void addModel();

private:
    OllamaModelSearchLineEdit *const mSearchLineEdit;
    OllamaModelsInfosCategoriesComboBox *const mCategoriesComboBox;
    QToolButton *const mAddModelButton;
};
