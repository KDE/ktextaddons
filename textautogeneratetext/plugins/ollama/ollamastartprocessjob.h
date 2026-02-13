/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollama_export.h"
#include <QObject>
class OllamaManager;
class QProcess;
class TEXTAUTOGENERATEOLLAMA_EXPORT OllamaStartProcessJob : public QObject
{
    Q_OBJECT
public:
    explicit OllamaStartProcessJob(OllamaManager *manager, QObject *parent = nullptr);
    ~OllamaStartProcessJob() override;

    [[nodiscard]] bool start();

    [[nodiscard]] QByteArray processOutputData() const;

Q_SIGNALS:
    void ollamaStarted();
    void ollamaFailed(const QString &errorStr);

private:
    TEXTAUTOGENERATEOLLAMA_NO_EXPORT void slotReadStandardOutput();
    OllamaManager *const mOllamaManager;
    QProcess *mProcess = nullptr;
    QByteArray mProcessOutputData;
};
