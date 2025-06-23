/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerategeneric_private_export.h"
#include <QWidget>
class GenericNetworkModelAvailableListView;
class TEXTAUTOGENERATEGENERICNETWORK_TESTS_EXPORT GenericNetworkModelAvailableWidget : public QWidget
{
    Q_OBJECT
public:
    explicit GenericNetworkModelAvailableWidget(QWidget *parent = nullptr);
    ~GenericNetworkModelAvailableWidget() override;

private:
    GenericNetworkModelAvailableListView *const mAvailableListView;
};
