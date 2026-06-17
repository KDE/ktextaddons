/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogeneratelmstudio_export.h"
#include <QObject>
class LMStudioManager;
class QProcess;
class TEXTAUTOGENERATELMSTUDIO_EXPORT LMStudioStartProcessJob : public QObject
{
    Q_OBJECT
public:
    explicit LMStudioStartProcessJob(LMStudioManager *manager, QObject *parent = nullptr);
    ~LMStudioStartProcessJob() override;

    [[nodiscard]] bool start();

Q_SIGNALS:
    void lmsStarted();
    void lmsFailed(const QString &errorStr);

private:
    TEXTAUTOGENERATELMSTUDIO_NO_EXPORT void slotReadStandardOutput();
    TEXTAUTOGENERATELMSTUDIO_NO_EXPORT void slotReadErrorOutput();
    LMStudioManager *const mLMStudioManager;
    QProcess *mProcess = nullptr;
    QByteArray mProcessOutputData;
};
