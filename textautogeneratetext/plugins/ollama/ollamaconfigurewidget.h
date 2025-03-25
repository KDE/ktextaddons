/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>
class QLineEdit;
class QComboBox;
class QPlainTextEdit;
class KMessageWidget;
class OllamaConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaConfigureWidget(QWidget *parent = nullptr);
    ~OllamaConfigureWidget() override;

    void loadSettings();
    void saveSettings();

private:
    void fillModels();
    QLineEdit *const mServerUrl;
    QPlainTextEdit *const mPrompt;
    QComboBox *const mModelComboBox;
    KMessageWidget *const mMessageWidget;
};
