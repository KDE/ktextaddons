/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QDialog>

#include "textautogeneratetextmcpprotocolwidgets_export.h"
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT AddMcpSteamableHttpServerHeaderConfigureDialog : public QDialog
{
    Q_OBJECT
public:
    explicit AddMcpSteamableHttpServerHeaderConfigureDialog(QWidget *parent = nullptr);
    ~AddMcpSteamableHttpServerHeaderConfigureDialog() override;
};
}
