/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QLineEdit>

class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelSearchLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit OllamaModelSearchLineEdit(QWidget *parent = nullptr);
    ~OllamaModelSearchLineEdit() override;
};
