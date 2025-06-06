/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateopenai_export.h"
#include <QDialog>
class OpenAIConfigureWidget;
class TEXTAUTOGENERATEOPENAI_EXPORT OpenAIConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit OpenAIConfigureDialog(QWidget *parent = nullptr);
    ~OpenAIConfigureDialog() override;

    void setApiKey(const QString &key);
    [[nodiscard]] QString apiKey() const;

private:
    TEXTAUTOGENERATEOPENAI_NO_EXPORT void readConfig();
    TEXTAUTOGENERATEOPENAI_NO_EXPORT void writeConfig();
    OpenAIConfigureWidget *const mOpenaiConfigureWidget;
};
