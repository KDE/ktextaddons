/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include <QObject>

class TextToSpeechKokoroUtilsTest : public QObject
{
    Q_OBJECT
public:
    explicit TextToSpeechKokoroUtilsTest(QObject *parent = nullptr);
    ~TextToSpeechKokoroUtilsTest() override = default;

private Q_SLOTS:
    void shouldHavePythonScript();
};
