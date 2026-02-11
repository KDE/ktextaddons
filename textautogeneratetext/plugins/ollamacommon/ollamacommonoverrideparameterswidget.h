/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollamacommon_export.h"
#include <QWidget>
class QDoubleSpinBox;
class QSpinBox;
class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonOverrideParametersWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaCommonOverrideParametersWidget(QWidget *parent = nullptr);
    ~OllamaCommonOverrideParametersWidget() override;

private:
    QDoubleSpinBox *const mTemperature;
    QSpinBox *const mSeed;
};
