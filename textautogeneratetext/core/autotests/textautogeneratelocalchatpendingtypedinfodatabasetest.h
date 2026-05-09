/*
   SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateLocalChatPendingTypedInfoDatabaseTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateLocalChatPendingTypedInfoDatabaseTest(QObject *parent = nullptr);
    ~TextAutoGenerateLocalChatPendingTypedInfoDatabaseTest() override = default;
private Q_SLOTS:
    void initTestCase();
    void shouldDefaultValues();
    void shouldVerifyDbFileName();
    void shouldStoreRoomPendingTypedInfo();
    void shouldDeleteRoomPendingTypedInfo();
    void shouldDeleteRoomPendingTypedInfoInvalidRoomId();
    void shouldExtractJsonFromDatabase();
};
