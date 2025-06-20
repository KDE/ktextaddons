/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_export.h"
#include <QWidget>
class QLineEdit;
class OllamaComboBoxWidget;
class QPlainTextEdit;
class KMessageWidget;
class OllamaManager;
class QDoubleSpinBox;
class QSpinBox;
class TEXTAUTOGENERATEOLLAMA_EXPORT OllamaConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaConfigureWidget(OllamaManager *manager, QWidget *parent = nullptr);
    ~OllamaConfigureWidget() override;

    void loadSettings();
    void saveSettings();

private:
    void fillModels();
    QLineEdit *const mName;
    QLineEdit *const mServerUrl;
    QPlainTextEdit *const mPrompt;
    OllamaComboBoxWidget *const mModelComboBoxWidget;
    KMessageWidget *const mMessageWidget;
    QDoubleSpinBox *const mTemperature;
    QSpinBox *const mSeed;
    OllamaManager *const mManager;
};
