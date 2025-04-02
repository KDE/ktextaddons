/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QDialog>
class OllamaConfigureWidget;
class OllamaConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OllamaConfigureDialog(QWidget *parent = nullptr);
    ~OllamaConfigureDialog() override;

private:
    void slotAccepted();
    void readConfig();
    void writeConfig();
    OllamaConfigureWidget *const mOllamaConfigureWidget;
};
