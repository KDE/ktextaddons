/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QDialog>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateTextInstancesManagerDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextInstancesManagerDialog(QWidget *parent = nullptr);
    ~TextAutoGenerateTextInstancesManagerDialog() override;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void readConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void writeConfig();
};
}
