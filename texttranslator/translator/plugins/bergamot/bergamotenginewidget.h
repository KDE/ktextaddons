/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QWidget>

class BergamotEngineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BergamotEngineWidget(QWidget *parent = nullptr);
    ~BergamotEngineWidget() override;
};
