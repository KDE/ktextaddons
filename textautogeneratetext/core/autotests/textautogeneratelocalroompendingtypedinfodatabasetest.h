/*
   SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateLocalRoomPendingTypedInfoDatabaseTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateLocalRoomPendingTypedInfoDatabaseTest(QObject *parent = nullptr);
    ~TextAutoGenerateLocalRoomPendingTypedInfoDatabaseTest() override = default;
private Q_SLOTS:
    void initTestCase();
    void shouldDefaultValues();
    void shouldVerifyDbFileName();
    void shouldStoreRoomPendingTypedInfo();
    void shouldDeleteRoomPendingTypedInfo();
    void shouldDeleteRoomPendingTypedInfoInvalidRoomId();
    void shouldExtractJsonFromDatabase();
};
