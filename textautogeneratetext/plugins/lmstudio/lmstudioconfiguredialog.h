/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "modelsmanager/lmstudiomodelinstalledwidget.h"
#include "textautogeneratelmstudio_export.h"
#include <KPageDialog>
class LMStudioConfigureWidget;
class LMStudioManager;
class LMStudioPlugin;
class TEXTAUTOGENERATELMSTUDIO_EXPORT LMStudioConfigureDialog : public KPageDialog
{
    Q_OBJECT
public:
    explicit LMStudioConfigureDialog(LMStudioManager *manager, LMStudioPlugin *plugin, QWidget *parent = nullptr);
    ~LMStudioConfigureDialog() override;

private:
    TEXTAUTOGENERATELMSTUDIO_NO_EXPORT void slotAccepted();
    TEXTAUTOGENERATELMSTUDIO_NO_EXPORT void readConfig();
    TEXTAUTOGENERATELMSTUDIO_NO_EXPORT void writeConfig();
    TEXTAUTOGENERATELMSTUDIO_NO_EXPORT void slotRestoreDefaults();
    LMStudioConfigureWidget *const mConfigureWidget;
    LMStudioModelInstalledWidget *const mModelInstalledWidget;
};
