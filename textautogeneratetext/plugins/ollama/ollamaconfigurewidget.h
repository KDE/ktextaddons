/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_export.h"
#include <QWidget>
class OllamaCommonOverrideParametersWidget;
class QLineEdit;
class QSpinBox;
class OllamaCommonComboBoxWidget;
class OllamaManager;
class OllamaConfigureCustomizeWidget;
class OllamaCommonKeepAliveParametersWidget;
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
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void showModelInfo(const QString &modelName);
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void displayModelInfo(const QString &modelStr);
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void slotOllamaStarted();
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void slotOllamaFailed(const QString &errorStr);
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void slotShowOllamaLog();
    QLineEdit *const mName;
    QSpinBox *const mPort;
    OllamaCommonComboBoxWidget *const mModelComboBoxWidget;
    TextAutoGenerateText::TextAutoGenerateNotWorkingMessageWidget *const mMessageWidget;
    OllamaManager *const mManager;
    OllamaConfigureCustomizeWidget *const mOllamaConfigureCustomizeWidget;
    OllamaCommonOverrideParametersWidget *const mOllamaCommonOverrideParametersWidget;
    OllamaCommonKeepAliveParametersWidget *const mOllamaCommonKeepAliveParametersWidget;
};
