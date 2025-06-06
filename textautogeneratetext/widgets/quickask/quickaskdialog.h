/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QDialog>
namespace TextAutoGenerateText
{
/**
 * @brief The QuickAskDialog class
 * @author Laurent Montel <montel@kde.org>
 */
class TEXTAUTOGENERATETEXT_EXPORT QuickAskDialog : public QDialog
{
    Q_OBJECT
public:
    explicit QuickAskDialog(QWidget *parent = nullptr);
    ~QuickAskDialog() override;

private:
    TEXTAUTOGENERATETEXT_NO_EXPORT void readConfig();
    TEXTAUTOGENERATETEXT_NO_EXPORT void writeConfig();
};
}
