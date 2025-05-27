/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerateollama_private_export.h"
#include <QWidget>
class QLineEdit;
class TEXTAUTOGENERATEOLLAMA_TESTS_EXPORT OllamaModelDownloadFromNameWidget : public QWidget
{
    Q_OBJECT
public:
    explicit OllamaModelDownloadFromNameWidget(QWidget *parent = nullptr);
    ~OllamaModelDownloadFromNameWidget() override;
    [[nodiscard]] QString modelName() const;

private:
    QLineEdit *const mModelNameLineEdit;
};
