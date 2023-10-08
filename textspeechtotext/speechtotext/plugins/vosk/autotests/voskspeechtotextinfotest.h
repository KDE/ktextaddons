/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class VoskSpeechToTextInfoTest : public QObject
{
    Q_OBJECT
public:
    explicit VoskSpeechToTextInfoTest(QObject *parent = nullptr);
    ~VoskSpeechToTextInfoTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
