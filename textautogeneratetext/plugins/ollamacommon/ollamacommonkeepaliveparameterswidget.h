/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "ollamacommonsettings.h"
#include "textautogenerateollamacommon_export.h"
#include <QWidget>
class QSpinBox;
class OllamaCommonKeepAliveParametersComboBox;
class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonKeepAliveParametersWidget : public QWidget
{
    Q_OBJECT
public:
    struct KeepAliveInfo {
        OllamaCommonSettings::KeepAliveType keepAliveType = OllamaCommonSettings::KeepAliveType::Unknown;
        int minutes = 1;
    };

    explicit OllamaCommonKeepAliveParametersWidget(QWidget *parent = nullptr);
    ~OllamaCommonKeepAliveParametersWidget() override;

    [[nodiscard]] KeepAliveInfo keepAliveInfo() const;
    void setKeepAliveInfo(const KeepAliveInfo &info);

private:
    TEXTAUTOGENERATEOLLAMACOMMON_NO_EXPORT void slotKeepAliveChanged();
    OllamaCommonKeepAliveParametersComboBox *const mOllamaCommonKeepAliveParametersComboBox;
    QSpinBox *const mKeepAliveMinutes;
};
