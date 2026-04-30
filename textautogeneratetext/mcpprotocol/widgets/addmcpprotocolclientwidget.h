/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolwidgets_export.h"
#include <QWidget>
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT AddMcpProtocolClientWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddMcpProtocolClientWidget(QWidget *parent = nullptr);
    ~AddMcpProtocolClientWidget() override;
};
}
