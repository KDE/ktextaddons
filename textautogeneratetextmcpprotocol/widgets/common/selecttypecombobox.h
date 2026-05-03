/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "mcpprotocolwidgets_private_export.h"
#include <QComboBox>
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_TESTS_EXPORT SelectTypeComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit SelectTypeComboBox(QWidget *parent = nullptr);
    ~SelectTypeComboBox() override;

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLWIDGETS_NO_EXPORT void fill();
};
}
