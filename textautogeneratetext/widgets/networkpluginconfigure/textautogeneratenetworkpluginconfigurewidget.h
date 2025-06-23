/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QWidget>
class KPasswordLineEdit;
class QLineEdit;
class QSpinBox;
class QDoubleSpinBox;
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateNetworkPluginConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutoGenerateNetworkPluginConfigureWidget(QWidget *parent = nullptr);
    ~TextAutoGenerateNetworkPluginConfigureWidget() override;

    void setApiKey(const QString &key);
    [[nodiscard]] QString apiKey() const;

    void setInstanceName(const QString &name);
    [[nodiscard]] QString instanceName() const;

    void setTemperature(double temp);
    [[nodiscard]] double temperature() const;

    void setMaxTokens(int tokens);
    [[nodiscard]] int tokens() const;

private:
    KPasswordLineEdit *const mApiKey;
    QLineEdit *const mInstanceName;
    QSpinBox *const mMaxToken;
    QDoubleSpinBox *const mTemperature;
};
}
