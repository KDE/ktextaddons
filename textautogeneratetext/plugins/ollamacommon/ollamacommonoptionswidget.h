/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollamacommon_export.h"
#include <QWidget>
class QCheckBox;
class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonOptionsWidget : public QWidget
{
    Q_OBJECT
public:
    struct OllamaCommonOptionsInfo {
        bool exposeToNetwork = false;
    };

    explicit OllamaCommonOptionsWidget(QWidget *parent = nullptr);
    ~OllamaCommonOptionsWidget() override;

    [[nodiscard]] OllamaCommonOptionsInfo optionsInfo() const;
    void setOptionsInfo(const OllamaCommonOptionsInfo &info);

private:
    QCheckBox *const mExpose;
};
