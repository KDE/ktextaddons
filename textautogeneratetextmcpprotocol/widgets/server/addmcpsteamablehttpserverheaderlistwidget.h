/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QListWidget>

#include "textautogeneratetextmcpprotocolwidgets_export.h"
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT AddMcpSteamableHttpServerHeaderListWidget : public QListWidget
{
    Q_OBJECT
public:
    explicit AddMcpSteamableHttpServerHeaderListWidget(QWidget *parent = nullptr);
    ~AddMcpSteamableHttpServerHeaderListWidget() override;
    void setHeaders(const QStringList &lst);
    [[nodiscard]] QStringList headers() const;
};
}
