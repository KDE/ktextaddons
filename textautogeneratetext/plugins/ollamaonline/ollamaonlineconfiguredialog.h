/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollamaonline_export.h"
#include <KPageDialog>

class TEXTAUTOGENERATEOLLAMAONLINE_EXPORT OllamaOnlineConfigureDialog : public KPageDialog
{
    Q_OBJECT
public:
    explicit OllamaOnlineConfigureDialog(QWidget *parent);
    ~OllamaOnlineConfigureDialog() override;

private:
    void readConfig();
    void writeConfig();
};
