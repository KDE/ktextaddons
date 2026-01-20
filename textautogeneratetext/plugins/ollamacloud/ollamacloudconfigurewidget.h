/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>
class QLineEdit;
class OllamaCloudManager;
class KPasswordLineEdit;
class OllamaCommonComboBoxWidget;
class OllamaCloudConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaCloudConfigureWidget(OllamaCloudManager *manager, QWidget *parent = nullptr);
    ~OllamaCloudConfigureWidget() override;

    void saveSettings();

Q_SIGNALS:
    void enableOkButton(bool enabled);

private:
    void fillModels();
    void loadSettings();
    void showModelInfo(const QString &modelName);
    void displayModelInfo(const QString &modelStr);
    QLineEdit *const mName;
    QLineEdit *const mServerUrl;
    KPasswordLineEdit *const mApiKey;
    OllamaCloudManager *const mManager;
    OllamaCommonComboBoxWidget *const mOllamaComboBoxWidget;
};
