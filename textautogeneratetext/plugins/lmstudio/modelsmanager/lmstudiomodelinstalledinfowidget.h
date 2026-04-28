/*
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratelmstudio_private_export.h"
#include <QWidget>

class TEXTAUTOGENERATELMSTUDIO_TESTS_EXPORT LMStudioModelInstalledInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit LMStudioModelInstalledInfoWidget(QWidget *parent = nullptr);
    ~LMStudioModelInstalledInfoWidget() override;
};
