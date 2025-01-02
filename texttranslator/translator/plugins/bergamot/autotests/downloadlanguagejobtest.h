/*
  SPDX-FileCopyrightText: 2023-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class DownloadLanguageJobTest : public QObject
{
    Q_OBJECT
public:
    explicit DownloadLanguageJobTest(QObject *parent = nullptr);
    ~DownloadLanguageJobTest() override = default;
private Q_SLOTS:
    void shouldHaveDefaultValues();
};
