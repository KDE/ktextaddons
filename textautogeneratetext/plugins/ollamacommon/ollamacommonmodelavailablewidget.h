/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollamacommon_export.h"
#include <QWidget>
#include <TextAutoGenerateText/TextAutoGenerateManager>
namespace TextAutoGenerateText
{
class TextAutoGenerateModelAvailableListView;
class TextAutoGenerateModelSearchLineEdit;
}
class OllamaCommonModelsInfosCategoriesComboBox;
class OllamaCommonModelAvailableInfosSortProxyModel;
class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonModelAvailableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaCommonModelAvailableWidget(QWidget *parent = nullptr);
    ~OllamaCommonModelAvailableWidget() override;

private:
    TextAutoGenerateText::TextAutoGenerateModelAvailableListView *const mAvailableListView;
    TextAutoGenerateText::TextAutoGenerateModelSearchLineEdit *const mSearchLineEdit;
    OllamaCommonModelsInfosCategoriesComboBox *const mCategoriesComboBox;
    OllamaCommonModelAvailableInfosSortProxyModel *const mProxyModel;
};
