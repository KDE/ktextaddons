/*
  SPDX-FileCopyrightText: 2023-2024 Laurent Montel <montel.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class SpeechToTextConfigureDialogTest : public QObject
{
    Q_OBJECT
public:
    explicit SpeechToTextConfigureDialogTest(QObject *parent = nullptr);
    ~SpeechToTextConfigureDialogTest() override = default;

private Q_SLOTS:
    void shouldHaveDefaultValues();
};
