/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratetext_export.h"
#include <QDialog>
namespace TextAutogenerateText
{
class TextAutogenerateWidget;
class TEXTAUTOGENERATETEXT_EXPORT TextAutogenerateDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutogenerateDialog(QWidget *parent = nullptr);
    ~TextAutogenerateDialog() override;

private:
    void readConfig();
    void writeConfig();
    TextAutogenerateWidget *const mTextAutogenerateWidget;
};
}
