/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QComboBox>
namespace TextAutoGenerateTextMcpProtocolWidgets
{
class SelectTypeComboBox : public QComboBox
{
    Q_OBJECT
public:
    explicit SelectTypeComboBox(QWidget *parent = nullptr);
    ~SelectTypeComboBox() override;
};
}
