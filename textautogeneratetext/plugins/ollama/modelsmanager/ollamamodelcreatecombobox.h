/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QComboBox>

class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelCreateComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit OllamaModelCreateComboBox(QWidget *parent = nullptr);
    ~OllamaModelCreateComboBox() override;

    [[nodiscard]] QString modelName() const;

private:
    void fillEngine();
};
