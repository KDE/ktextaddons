/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class LMStudioModelInstalledInfoTest : public QObject
{
    Q_OBJECT
public:
    explicit LMStudioModelInstalledInfoTest(QObject *parent = nullptr);
    ~LMStudioModelInstalledInfoTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
