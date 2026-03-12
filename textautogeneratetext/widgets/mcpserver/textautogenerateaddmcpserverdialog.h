/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QDialog>
namespace TextAutoGenerateText
{
class TextAutoGenerateAddMcpServerWidget;
class TextAutoGenerateAddMcpServerDialog : public QDialog
{
    Q_OBJECT
public:
    explicit TextAutoGenerateAddMcpServerDialog(QWidget *parent = nullptr);
    ~TextAutoGenerateAddMcpServerDialog() override;

private:
    TextAutoGenerateAddMcpServerWidget *const mTextAutoGenerateAddMcpServerWidget;
};
}
