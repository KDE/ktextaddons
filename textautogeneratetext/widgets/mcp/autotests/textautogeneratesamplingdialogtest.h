/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateSamplingDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateSamplingDialogTest(QObject *parent = nullptr);
    ~TextAutoGenerateSamplingDialogTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldShowRequest();
};
