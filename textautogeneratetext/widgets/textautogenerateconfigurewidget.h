/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
namespace TextAutoGenerateText
{
class TextAutoGenerateManager;
class TextAutoGenerateTextConfigureComboWidget;
/**
 * @brief The TextAutoGenerateConfigureWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateConfigureWidget(TextAutoGenerateText::TextAutoGenerateManager *manager, QWidget *parent = nullptr);
    ~TextAutoGenerateConfigureWidget() override;

    void loadSettings();
    void saveSettings();

private:
    TextAutoGenerateTextConfigureComboWidget *const mPluginComboBox;
};

}
