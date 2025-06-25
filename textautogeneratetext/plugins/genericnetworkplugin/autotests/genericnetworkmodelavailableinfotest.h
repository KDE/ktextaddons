/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class GenericNetworkModelAvailableInfoTest : public QObject
{
    Q_OBJECT
public:
    explicit GenericNetworkModelAvailableInfoTest(QObject *parent = nullptr);
    ~GenericNetworkModelAvailableInfoTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
