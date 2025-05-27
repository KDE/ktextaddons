/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QDialog>
class OllamaModelDownloadFromNameWidget;
class OllamaModelDownloadFromNameDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OllamaModelDownloadFromNameDialog(QWidget *parent = nullptr);
    ~OllamaModelDownloadFromNameDialog() override;

private:
    OllamaModelDownloadFromNameWidget *const mOllamaModelDownloadFromNameWidget;
};
