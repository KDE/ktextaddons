/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QWidget>
class OllamaModelInstalledListView;
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelInstalledWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelInstalledWidget(QWidget *parent = nullptr);
    ~OllamaModelInstalledWidget() override;

private:
    OllamaModelInstalledListView *const mOllamaModelInstalledListView;
};
