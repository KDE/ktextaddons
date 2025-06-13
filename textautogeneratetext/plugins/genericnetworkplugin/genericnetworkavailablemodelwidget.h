/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QWidget>
class GenericNetworkManager;
class GenericNetworkAvailableModelWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GenericNetworkAvailableModelWidget(GenericNetworkManager *manager, QWidget *parent = nullptr);
    ~GenericNetworkAvailableModelWidget() override;
};
