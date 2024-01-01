/*
  SPDX-FileCopyrightText: 2022-2024 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QDialog>
class LibreTranslateEngineConfigureWidget;
class LibreTranslateEngineConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit LibreTranslateEngineConfigureDialog(QWidget *parent = nullptr);
    ~LibreTranslateEngineConfigureDialog() override;

    [[nodiscard]] QString serverUrl() const;
    void setServerUrl(const QString &serverUrl);

    [[nodiscard]] QString apiKey() const;
    void setApiKey(const QString &key);

    [[nodiscard]] bool serverRequiredApiKey() const;
    void setServerRequiredApiKey(bool state);

private:
    LibreTranslateEngineConfigureWidget *const mConfigureWidget;
};
