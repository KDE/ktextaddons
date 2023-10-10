/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class GenerateInstalledLanguageInfoJob : public QObject
{
    Q_OBJECT
public:
    explicit GenerateInstalledLanguageInfoJob(QObject *parent = nullptr);
    ~GenerateInstalledLanguageInfoJob() override;

    void start();
    Q_REQUIRED_RESULT bool canStart() const;
};
