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
    struct OverrideParametersInfo {
        double temperature = 0.0;
        int seed = 1.0;
    };

    explicit OllamaCommonOverrideParametersWidget(QWidget *parent = nullptr);
    ~OllamaCommonOverrideParametersWidget() override;

    [[nodiscard]] OverrideParametersInfo parametersInfo() const;

    void setParametersInfo(const OverrideParametersInfo &info);

private:
    QDoubleSpinBox *const mTemperature;
    QSpinBox *const mSeed;
    QSpinBox *const mContextWindowSize;
};
Q_DECLARE_TYPEINFO(OllamaCommonOverrideParametersWidget::OverrideParametersInfo, Q_RELOCATABLE_TYPE);
