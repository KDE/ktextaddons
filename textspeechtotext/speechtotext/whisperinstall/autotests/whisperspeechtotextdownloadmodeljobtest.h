/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class WhisperSpeechToTextDownloadModelJobTest : public QObject
{
    Q_OBJECT
public:
    explicit WhisperSpeechToTextDownloadModelJobTest(QObject *parent = nullptr);
    ~WhisperSpeechToTextDownloadModelJobTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldAssignModel();
    void shouldParseEvents();
    void shouldParseEvents_data();
    void shouldNotParseInvalidLine();
    void shouldNotStartWithoutModel();
};
