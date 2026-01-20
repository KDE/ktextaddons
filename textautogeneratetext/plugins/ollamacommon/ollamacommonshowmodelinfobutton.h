/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogenerateollamacommon_export.h"
#include <QToolButton>

class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonShowModelInfoButton : public QToolButton
{
    Q_OBJECT
public:
    explicit OllamaCommonShowModelInfoButton(QWidget *parent = nullptr);
    ~OllamaCommonShowModelInfoButton() override;

Q_SIGNALS:
    void showModelInfoRequested();
};
