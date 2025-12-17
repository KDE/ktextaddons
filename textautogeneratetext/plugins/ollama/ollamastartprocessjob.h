/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QObject>

class OllamaStartProcessJob : public QObject
{
    Q_OBJECT
public:
    explicit OllamaStartProcessJob(QObject *parent = nullptr);
    ~OllamaStartProcessJob() override;

    void start();

Q_SIGNALS:
    void ollamaStarted();
    void ollamaFailed(const QString &errorStr);
};
