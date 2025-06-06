/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include "textautogeneratetext_export.h"
#include <QWidget>
class KPasswordLineEdit;
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT NetworkPluginConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit NetworkPluginConfigureWidget(QWidget *parent = nullptr);
    ~NetworkPluginConfigureWidget() override;

    void setApiKey(const QString &key);
    [[nodiscard]] QString apiKey() const;

private:
    KPasswordLineEdit *const mApiKey;
};
}
