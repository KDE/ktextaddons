/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class AddMcpServerBaseWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddMcpServerBaseWidget(QWidget *parent = nullptr);
    ~AddMcpServerBaseWidget() override;
};
}
