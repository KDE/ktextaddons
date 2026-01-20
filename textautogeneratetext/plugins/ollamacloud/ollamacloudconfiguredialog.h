/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollamacloud_export.h"
#include <KPageDialog>
class OllamaCloudConfigureWidget;
class OllamaCloudManager;
class TEXTAUTOGENERATEOLLAMACLOUD_EXPORT OllamaCloudConfigureDialog : public KPageDialog
{
    Q_OBJECT
public:
    explicit OllamaCloudConfigureDialog(OllamaCloudManager *manager, QWidget *parent);
    ~OllamaCloudConfigureDialog() override;

private:
    TEXTAUTOGENERATEOLLAMACLOUD_NO_EXPORT void readConfig();
    TEXTAUTOGENERATEOLLAMACLOUD_NO_EXPORT void writeConfig();
    TEXTAUTOGENERATEOLLAMACLOUD_NO_EXPORT void slotAccepted();
    OllamaCloudConfigureWidget *const mOllamaCloudConfigureWidget;
};
