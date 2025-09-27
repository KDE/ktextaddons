/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QObject>

class TextAutoGenerateReplyTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateReplyTest(QObject *parent = nullptr);
    ~TextAutoGenerateReplyTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldParseToolCalls();
    void shouldParseToolCalls_data();
};
