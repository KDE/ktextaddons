/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>

#include "mcpprotocolwidgets_private_export.h"
class QPushButton;
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class AddMcpStreamableHttpServerHeaderListWidget;
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT AddMcpStreamableHttpServerHeaderWidget : public QWidget
{
    Q_OBJECT
public:
    explicit AddMcpStreamableHttpServerHeaderWidget(QWidget *parent = nullptr);
    ~AddMcpStreamableHttpServerHeaderWidget() override;

    [[nodiscard]] QStringList headers() const;
    void setHeaders(const QStringList &h);

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void slotModifyHeader();
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void slotAddHeader();
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void slotRemoveHeader();
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void updateButtons();
    AddMcpStreamableHttpServerHeaderListWidget *const mListBox;
    QPushButton *mModifyHeaderButton = nullptr;
    QPushButton *mRemoveHeaderButton = nullptr;
};
}
