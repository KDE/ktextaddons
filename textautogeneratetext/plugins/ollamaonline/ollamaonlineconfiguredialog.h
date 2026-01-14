/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollamaonline_export.h"
#include <KPageDialog>
class OllamaOnlineConfigureWidget;
class OllamaOnlineManager;
class TEXTAUTOGENERATEOLLAMAONLINE_EXPORT OllamaOnlineConfigureDialog : public KPageDialog
{
    Q_OBJECT
public:
    explicit OllamaOnlineConfigureDialog(OllamaOnlineManager *manager, QWidget *parent);
    ~OllamaOnlineConfigureDialog() override;

private:
    TEXTAUTOGENERATEOLLAMAONLINE_NO_EXPORT void readConfig();
    TEXTAUTOGENERATEOLLAMAONLINE_NO_EXPORT void writeConfig();
    TEXTAUTOGENERATEOLLAMAONLINE_NO_EXPORT void slotAccepted();
    OllamaOnlineConfigureWidget *const mOllamaOnlineConfigureWidget;
};
