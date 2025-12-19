/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_export.h"
#include <KPageDialog>
class OllamaConfigureWidget;
class OllamaManager;
class OllamaModelAvailableWidget;
class OllamaModelInstalledWidget;
class OllamaModelCreateWidget;
class TEXTAUTOGENERATEOLLAMA_EXPORT OllamaConfigureDialog : public KPageDialog
{
    Q_OBJECT
public:
    explicit OllamaConfigureDialog(OllamaManager *manager, QWidget *parent = nullptr);
    ~OllamaConfigureDialog() override;

private:
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void slotAccepted();
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void readConfig();
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void writeConfig();
    OllamaConfigureWidget *const mOllamaConfigureWidget;
    OllamaModelAvailableWidget *const mOllamaModelWidget;
    OllamaModelInstalledWidget *const mOllamaModelInstalledWidget;
    OllamaModelCreateWidget *const mOllamaModelCreateWidget;
};
