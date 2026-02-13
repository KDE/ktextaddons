/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QPlainTextEdit>

class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaLogTextEdit : public QPlainTextEdit
{
    Q_OBJECT
public:
    explicit OllamaLogTextEdit(QWidget *parent = nullptr);
    ~OllamaLogTextEdit() override;
};
