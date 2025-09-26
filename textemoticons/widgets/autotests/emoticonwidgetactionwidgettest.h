/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include <QObject>

class EmoticonWidgetActionWidgetTest : public QObject
{
    Q_OBJECT
public:
    explicit EmoticonWidgetActionWidgetTest(QObject *parent = nullptr);
    ~EmoticonWidgetActionWidgetTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
