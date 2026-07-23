/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>

#include "textautogeneratetextmcpprotocolwidgets_export.h"

namespace TextAutoGenerateTextMcpProtocolWidgets
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT AddMcpSteamableHttpServerHeaderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddMcpSteamableHttpServerHeaderWidget(QWidget *parent = nullptr);
    ~AddMcpSteamableHttpServerHeaderWidget() override;
};
}
