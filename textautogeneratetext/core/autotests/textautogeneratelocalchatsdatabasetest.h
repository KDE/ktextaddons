/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateLocalChatsDatabaseTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateLocalChatsDatabaseTest(QObject *parent = nullptr);
    ~TextAutoGenerateLocalChatsDatabaseTest() override = default;

private Q_SLOTS:
    void initTestCase();
    void shouldDefaultValues();
    void shouldVerifyDbFileName();
    void shouldStoreChats();
    void shouldDeleteChats();
};
