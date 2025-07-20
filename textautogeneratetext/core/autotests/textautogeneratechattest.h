/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateChatTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateChatTest(QObject *parent = nullptr);
    ~TextAutoGenerateChatTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldSerializeDeserialize();
};
