/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class GenericNetworkServerInfoTest : public QObject
{
    Q_OBJECT
public:
    explicit GenericNetworkServerInfoTest(QObject *parent = nullptr);
    ~GenericNetworkServerInfoTest() override = default;

private Q_SLOTS:
    void shouldConvertPluginNetworkTypeFromString();
};
