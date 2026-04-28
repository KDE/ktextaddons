/*
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratelmstudio_private_export.h"
#include <QWidget>
class LMStudioManager;
class LMStudioModelInstalledWidget;
class TEXTAUTOGENERATELMSTUDIO_TESTS_EXPORT LMStudioInstalledModelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LMStudioInstalledModelWidget(LMStudioManager *manager, QWidget *parent = nullptr);
    ~LMStudioInstalledModelWidget() override;

private:
    LMStudioModelInstalledWidget *const mLMStudioModelInstalledWidget;
};
