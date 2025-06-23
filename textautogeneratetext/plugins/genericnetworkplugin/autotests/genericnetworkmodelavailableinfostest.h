/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class GenericNetworkModelAvailableInfosTest : public QObject
{
    Q_OBJECT
public:
    explicit GenericNetworkModelAvailableInfosTest(QObject *parent = nullptr);
    ~GenericNetworkModelAvailableInfosTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
