/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateChatsModelTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateChatsModelTest(QObject *parent = nullptr);
    ~TextAutoGenerateChatsModelTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldCheckHasAtLeastOneNotArchivedChat();
};
