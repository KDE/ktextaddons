/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include <QObject>

class TextAutoGenerateMcpSamplingJobTest : public QObject
{
    Q_OBJECT
public:
    explicit TextAutoGenerateMcpSamplingJobTest(QObject *parent = nullptr);
    ~TextAutoGenerateMcpSamplingJobTest() override = default;

private Q_SLOTS:
    void shouldConvertMessages();
    void shouldNotConvertUnsupportedContent();
    void shouldFailWithoutPlugin();
    void shouldFailWhenPluginDoesNotSupportIt();
    void shouldReturnGeneratedMessage();
    void shouldFailWhenLlmFails();
};
