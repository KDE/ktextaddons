/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TextAutoGenerateMessageTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateMessageTest(QObject *parent = nullptr);
    ~TextAutoGenerateMessageTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldCheckFromString();
#if 0
    void shouldParseMessage();
    void shouldParseMessage_data();
#endif
};
