/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollamacommon_export.h"
#include <QWidget>
class OllamaCommonKeepAliveParametersComboBox;
class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonKeepAliveParametersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaCommonKeepAliveParametersWidget(QWidget *parent = nullptr);
    ~OllamaCommonKeepAliveParametersWidget() override;

private:
    OllamaCommonKeepAliveParametersComboBox *const mOllamaCommonKeepAliveParametersComboBox;
};
