/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogenerategeneric_private_export.h"
#include <QListView>

class TEXTAUTOGENERATEGENERICNETWORK_TESTS_EXPORT GenericNetworkModelAvailableListView : public QListView
{
    Q_OBJECT
public:
    explicit GenericNetworkModelAvailableListView(QWidget *parent = nullptr);
    ~GenericNetworkModelAvailableListView() override;
};
