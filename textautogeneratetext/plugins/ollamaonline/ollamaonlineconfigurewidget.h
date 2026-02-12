/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>
class QLineEdit;
class OllamaOnlineManager;
class KPasswordLineEdit;
class OllamaCommonComboBoxWidget;
class OllamaCommonOverrideParametersWidget;
class OllamaCommonKeepAliveParametersWidget;
class OllamaOnlineConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaOnlineConfigureWidget(OllamaOnlineManager *manager, QWidget *parent = nullptr);
    ~OllamaOnlineConfigureWidget() override;

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
    OllamaOnlineManager *const mManager;
    OllamaCommonComboBoxWidget *const mOllamaComboBoxWidget;
    OllamaCommonOverrideParametersWidget *const mOllamaCommonOverrideParametersWidget;
    OllamaCommonKeepAliveParametersWidget *const mOllamaCommonKeepAliveParametersWidget;
};
