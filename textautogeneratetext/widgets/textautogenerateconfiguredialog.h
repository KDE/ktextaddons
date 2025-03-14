/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <QDialog>
namespace TextAutogenerateText
{
class TextAutogenerateConfigureWidget;
class TEXTAUTOGENERATETEXT_EXPORT TextAutogenerateConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutogenerateConfigureDialog(QWidget *parent = nullptr);
    ~TextAutogenerateConfigureDialog() override;

private:
    TextAutogenerateConfigureWidget *const mTextAutogenerateConfigureWidget;
};
}
