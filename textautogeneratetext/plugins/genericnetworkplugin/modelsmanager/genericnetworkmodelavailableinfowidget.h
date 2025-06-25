/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerategeneric_private_export.h"
#include <QWidget>

class TEXTAUTOGENERATEGENERICNETWORK_TESTS_EXPORT GenericNetworkModelAvailableInfoWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GenericNetworkModelAvailableInfoWidget(QWidget *parent = nullptr);
    ~GenericNetworkModelAvailableInfoWidget() override;
};
