/*
 * SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include <QObject>

class TextAutoGenerateExportChatBaseJobTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateExportChatBaseJobTest(QObject *parent = nullptr);
    ~TextAutoGenerateExportChatBaseJobTest() override = default;
private Q_SLOTS:
    void shouldVerifyExportChatInfo();
};
