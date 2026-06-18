/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include <QObject>

class TextAutoGenerateExportChatAsJsonJobTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateExportChatAsJsonJobTest(QObject *parent = nullptr);
    ~TextAutoGenerateExportChatAsJsonJobTest() override = default;

private Q_SLOTS:
    void shouldEmitExportDoneOnSuccess();
    void shouldNotEmitExportDoneWhenWriteFails();
};
