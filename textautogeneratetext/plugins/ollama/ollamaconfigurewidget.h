/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_export.h"
#include <QWidget>
class QLineEdit;
class OllamaComboBoxWidget;
class OllamaManager;
class QDoubleSpinBox;
class QSpinBox;
class OllamaConfigureCustomizeWidget;
namespace TextAutoGenerateText
{
class TextAutoGenerateNotWorkingMessageWidget;
}
class TEXTAUTOGENERATEOLLAMA_EXPORT OllamaConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaConfigureWidget(OllamaManager *manager, QWidget *parent = nullptr);
    ~OllamaConfigureWidget() override;

    void loadSettings();
    void saveSettings();

Q_SIGNALS:
    void ollamaProcessOk(bool status);
    void enableOkButton(bool status);

private:
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void fillModels();
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void slotStartOllama();
    QLineEdit *const mName;
    QLineEdit *const mServerUrl;
    OllamaComboBoxWidget *const mModelComboBoxWidget;
    TextAutoGenerateText::TextAutoGenerateNotWorkingMessageWidget *const mMessageWidget;
    QDoubleSpinBox *const mTemperature;
    QSpinBox *const mSeed;
    OllamaManager *const mManager;
    OllamaConfigureCustomizeWidget *const mOllamaConfigureCustomizeWidget;
};
