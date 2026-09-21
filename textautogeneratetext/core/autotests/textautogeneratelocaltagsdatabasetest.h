/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateLocalTagsDatabaseTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateLocalTagsDatabaseTest(QObject *parent = nullptr);
    ~TextAutoGenerateLocalTagsDatabaseTest() override = default;

private Q_SLOTS:
    void initTestCase();
    void shouldDefaultValues();
    void shouldVerifyDbFileName();
    void shouldStoreTags();
    void shouldLoadTags();
    void shouldDeleteTags();
};
