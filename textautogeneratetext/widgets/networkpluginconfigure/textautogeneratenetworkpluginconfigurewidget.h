/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QWidget>
class KPasswordLineEdit;
class QLineEdit;
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

private:
    KPasswordLineEdit *const mApiKey;
    QLineEdit *const mInstanceName;
};
}
