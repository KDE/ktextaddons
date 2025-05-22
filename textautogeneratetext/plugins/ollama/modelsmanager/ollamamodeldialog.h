/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QDialog>
class OllamaModelWidget;
class OllamaModelDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OllamaModelDialog(QWidget *parent = nullptr);
    ~OllamaModelDialog() override;

private:
    OllamaModelWidget *const mOllamaModelWidget;
    void readConfig();
    void writeConfig();
};
