/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>
namespace TextAutogenerateText
{
class TextAutogenerateConfigureWidget : public QWidget
{
    Q_OBJECT
public:
    explicit TextAutogenerateConfigureWidget(QWidget *parent = nullptr);
    ~TextAutogenerateConfigureWidget() override;
};

}
