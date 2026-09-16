/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class WhisperSpeechToTextInstallJobTest : public QObject
{
    Q_OBJECT
public:
    explicit WhisperSpeechToTextInstallJobTest(QObject *parent = nullptr);
    ~WhisperSpeechToTextInstallJobTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldAssignModules();
    void shouldNotStartWithoutModules();
};
