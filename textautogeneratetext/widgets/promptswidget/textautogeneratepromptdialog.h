/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_private_export.h"
#include <QDialog>
namespace TextAutoGenerateText
{
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGeneratePromptDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGeneratePromptDialog(QWidget *parent = nullptr);
    ~TextAutoGeneratePromptDialog() override;
};
}
