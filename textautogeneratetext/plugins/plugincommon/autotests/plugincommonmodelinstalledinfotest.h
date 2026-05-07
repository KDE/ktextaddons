/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

#include "plugincommonmodelinstalledinfo.h"

class TestModelInstalledInfo : public PluginCommonModelInstalledInfo
{
public:
    void parseInfo([[maybe_unused]] const QJsonObject &obj) override
    {
    }
};

class PluginCommonModelInstalledInfoTest : public QObject
{
    Q_OBJECT
public:
    explicit PluginCommonModelInstalledInfoTest(QObject *parent = nullptr);
    ~PluginCommonModelInstalledInfoTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
