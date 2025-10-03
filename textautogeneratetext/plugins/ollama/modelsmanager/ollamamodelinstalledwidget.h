/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QWidget>
class OllamaModelInstalledListView;
class OllamaModelInstalledInfoWidget;
class OllamaManager;
class QToolButton;
class OllamaModelsInfosCategoriesComboBox;
class OllamaModelInstalledInfosSortProxyModel;
namespace TextAutoGenerateText
{
class TextAutoGenerateModelSearchLineEdit;
}
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelInstalledWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelInstalledWidget(OllamaManager *manager, QWidget *parent = nullptr);
    ~OllamaModelInstalledWidget() override;

private:
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void slotRemoveModel();
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void slotClicked(const QModelIndex &);
    OllamaModelInstalledListView *const mOllamaModelInstalledListView;
    TextAutoGenerateText::TextAutoGenerateModelSearchLineEdit *const mSearchLineEdit;
    OllamaModelsInfosCategoriesComboBox *const mCategoriesComboBox;
    QToolButton *const mRemoveModelButton;
    OllamaModelInstalledInfoWidget *const mOllamaModelInstalledInfoWidget;
    OllamaManager *const mManager;
    OllamaModelInstalledInfosSortProxyModel *const mProxyModel;
};
