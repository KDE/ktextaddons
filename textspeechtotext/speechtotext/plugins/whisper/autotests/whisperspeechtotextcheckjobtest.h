/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class WhisperSpeechToTextCheckJobTest : public QObject
{
    Q_OBJECT
public:
    explicit WhisperSpeechToTextCheckJobTest(QObject *parent = nullptr);
    ~WhisperSpeechToTextCheckJobTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldParseCheckResult_data();
    void shouldParseCheckResult();
    void shouldReportErrorString();
    void shouldAskToInstallPackagesWithoutVenv();
};
