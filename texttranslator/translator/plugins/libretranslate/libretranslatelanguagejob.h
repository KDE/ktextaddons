/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class LibreTranslateLanguageJob : public QObject
{
    Q_OBJECT
public:
    explicit LibreTranslateLanguageJob(QObject *parent = nullptr);
    ~LibreTranslateLanguageJob() override;

    [[nodiscard]] bool canStart() const;

    void start();
};
