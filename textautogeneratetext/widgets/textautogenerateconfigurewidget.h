/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QWidget>
namespace TextAutoGenerateText
{
class TextAutoGenerateTextConfigureComboWidget;
/**
 * @brief The TextAutogenerateConfigureWidget class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutogenerateConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutogenerateConfigureWidget(QWidget *parent = nullptr);
    ~TextAutogenerateConfigureWidget() override;

    void loadSettings();
    void saveSettings();

private:
    TextAutoGenerateTextConfigureComboWidget *const mPluginComboBox;
};

}
