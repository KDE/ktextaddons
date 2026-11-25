/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class LibreTranslateLanguagesJobTest : public QObject
{
    Q_OBJECT
public:
    explicit LibreTranslateLanguagesJobTest(QObject *parent = nullptr);
    ~LibreTranslateLanguagesJobTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
    void shouldParseLanguages();
    void shouldIgnoreInvalidLanguages();
};
