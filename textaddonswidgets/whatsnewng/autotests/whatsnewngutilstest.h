/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QObject>

class WhatsNewNgUtilsTest : public QObject
{
    Q_OBJECT
public:
    explicit WhatsNewNgUtilsTest(QObject *parent = nullptr);
    ~WhatsNewNgUtilsTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldGenerateCreateMD5();
    void shouldGenerateChangelog();
};
