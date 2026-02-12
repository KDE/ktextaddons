/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollamacommon_export.h"
#include <QWidget>
class QSpinBox;
class OllamaCommonKeepAliveParametersComboBox;
class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonKeepAliveParametersWidget : public QWidget
{
    Q_OBJECT
public:
    enum class KeepAliveType : uint8_t {
        Unknown = 0,
        KeepAliveForever,
        UnloadAfterUse,
        SetTimer,
    };
    Q_ENUM(KeepAliveType)

    struct KeepAliveInfo {
        KeepAliveType keepAliveType = KeepAliveType::Unknown;
        int minutes = 1;
    };

    explicit OllamaCommonKeepAliveParametersWidget(QWidget *parent = nullptr);
    ~OllamaCommonKeepAliveParametersWidget() override;

    [[nodiscard]] KeepAliveInfo keepAliveInfo() const;
    void setKeepAliveInfo(const KeepAliveInfo &info);

private:
    OllamaCommonKeepAliveParametersComboBox *const mOllamaCommonKeepAliveParametersComboBox;
    QSpinBox *const mKeepAliveMinutes;
};
Q_DECLARE_TYPEINFO(OllamaCommonKeepAliveParametersWidget::KeepAliveType, Q_RELOCATABLE_TYPE);
