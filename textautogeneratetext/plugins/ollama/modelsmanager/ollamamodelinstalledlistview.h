/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QListView>

class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelInstalledListView : public QListView
{
    Q_OBJECT
public:
    explicit OllamaModelInstalledListView(QWidget *parent = nullptr);
    ~OllamaModelInstalledListView() override;
};
