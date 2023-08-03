/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "libbergamot_private_export.h"
#include <QWidget>

class LIBBERGAMOT_TESTS_EXPORT BergamotEngineWidget : public QWidget
{
    Q_OBJECT
public:
    explicit BergamotEngineWidget(QWidget *parent = nullptr);
    ~BergamotEngineWidget() override;
};
