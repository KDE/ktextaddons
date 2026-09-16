/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class WhisperSpeechToTextModelsJobTest : public QObject
{
    Q_OBJECT
public:
    explicit WhisperSpeechToTextModelsJobTest(QObject *parent = nullptr);
    ~WhisperSpeechToTextModelsJobTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldParseModels();
    void shouldIgnoreModelsWithoutIdentifier();
    void shouldNotParseInvalidJson();
    void shouldReportTheDefaultModel();
    void shouldListTheModelsOfTheScript();
};
