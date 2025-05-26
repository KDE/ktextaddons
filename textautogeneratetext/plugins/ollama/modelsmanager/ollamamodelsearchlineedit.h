/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QLineEdit>

class OllamaModelSearchLineEdit : public QLineEdit
{
    Q_OBJECT
public:
    explicit OllamaModelSearchLineEdit(QWidget *parent = nullptr);
    ~OllamaModelSearchLineEdit() override;
};
