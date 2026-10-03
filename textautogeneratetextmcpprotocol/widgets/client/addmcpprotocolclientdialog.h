/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "mcpprotocolwidgets_private_export.h"
#include <QDialog>
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT AddMcpProtocolClientDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddMcpProtocolClientDialog(QWidget *parent = nullptr);
    ~AddMcpProtocolClientDialog() override;
};
}
