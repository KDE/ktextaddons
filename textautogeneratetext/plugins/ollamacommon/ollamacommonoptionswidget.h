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
    explicit OllamaCommonOptionsWidget(QWidget *parent = nullptr);
    ~OllamaCommonOptionsWidget() override;

private:
    QCheckBox *const mExpose;
};
