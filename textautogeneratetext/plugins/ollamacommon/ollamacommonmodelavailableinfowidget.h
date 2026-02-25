/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollamacommon_export.h"
#include <QWidget>

class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonModelAvailableInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaCommonModelAvailableInfoWidget(QWidget *parent = nullptr);
    ~OllamaCommonModelAvailableInfoWidget() override;
};
