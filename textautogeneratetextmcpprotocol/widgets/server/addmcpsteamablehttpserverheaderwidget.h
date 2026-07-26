/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>

#include "textautogeneratetextmcpprotocolwidgets_export.h"
class QListWidget;
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class AddMcpSteamableHttpServerHeaderListWidget;
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_EXPORT AddMcpSteamableHttpServerHeaderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddMcpSteamableHttpServerHeaderWidget(QWidget *parent = nullptr);
    ~AddMcpSteamableHttpServerHeaderWidget() override;

    [[nodiscard]] QStringList headers() const;
    void setHeaders(const QStringList &h);

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void slotModifyHeader();
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void slotAddHeader();
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void slotRemoveHeader();
    AddMcpSteamableHttpServerHeaderListWidget *const mListBox;
};
}
