/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QDialog>
class OllamaModelAvailableWidget;
class OllamaManager;
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelAvailableDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OllamaModelAvailableDialog(OllamaManager *manager, QWidget *parent = nullptr);
    ~OllamaModelAvailableDialog() override;

private:
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void readConfig();
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void writeConfig();
    OllamaModelAvailableWidget *const mOllamaModelWidget;
};
