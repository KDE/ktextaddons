/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QDialog>
class OllamaModelDownloadFromNameWidget;
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelDownloadFromNameDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OllamaModelDownloadFromNameDialog(QWidget *parent = nullptr);
    ~OllamaModelDownloadFromNameDialog() override;

    [[nodiscard]] QString modelName() const;

private:
    OllamaModelDownloadFromNameWidget *const mOllamaModelDownloadFromNameWidget;
};
