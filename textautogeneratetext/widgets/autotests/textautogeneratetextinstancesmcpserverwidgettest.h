/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TextAutoGenerateTextInstancesMcpServerWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateTextInstancesMcpServerWidgetTest(QObject *parent = nullptr);
    ~TextAutoGenerateTextInstancesMcpServerWidgetTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
