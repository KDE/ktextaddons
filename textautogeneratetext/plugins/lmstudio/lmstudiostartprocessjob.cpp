/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lmstudiostartprocessjob.h"
#include "autogeneratetext_lmstudio_debug.h"
#include "lmstudiomanager.h"
#include "lmstudiosettings.h"
#include <KLocalizedString>
#include <QProcess>
#include <TextAddonsWidgets/ExecutableUtils>

using namespace Qt::Literals::StringLiterals;
LMStudioStartProcessJob::LMStudioStartProcessJob(LMStudioManager *manager, QObject *parent)
    : QObject{parent}
    , mLMStudioManager(manager)
{
}

LMStudioStartProcessJob::~LMStudioStartProcessJob()
{
    if (mProcess) {
        mProcess->kill();
        mProcess->deleteLater();
    }
}

bool LMStudioStartProcessJob::start()
{
    const QString lmsPath = TextAddonsWidgets::ExecutableUtils::findExecutable(u"lms"_s);
    if (lmsPath.isEmpty()) {
        qCWarning(AUTOGENERATETEXT_LMSTUDIO_LOG) << "lmstudio doesn't exist";
        Q_EMIT lmsFailed(i18n("LMStudio not found on system."));
        deleteLater();
        return false;
    }
    if (!mLMStudioManager) {
        qCWarning(AUTOGENERATETEXT_LMSTUDIO_LOG) << "LMStudioManager is not defined";
        Q_EMIT lmsFailed(i18n("Impossible to start LMStudio."));
        deleteLater();
        return false;
    }

    mProcess = new QProcess(this);
    mProcess->setProgram(lmsPath);
    mProcess->setArguments({u"start"_s});
    connect(mProcess, &QProcess::readyReadStandardOutput, this, &LMStudioStartProcessJob::slotReadStandardOutput);
    connect(mProcess, &QProcess::readyReadStandardError, this, &LMStudioStartProcessJob::slotReadStandardOutput);
    mProcess->start();
    if (mProcess->waitForStarted()) {
        Q_EMIT lmsStarted();
    } else {
        qCWarning(AUTOGENERATETEXT_LMSTUDIO_LOG) << "Impossible to start lms process";
        Q_EMIT lmsFailed(i18n("Impossible to start LMStudio."));
        deleteLater();
        return false;
    }
    return true;
}

void LMStudioStartProcessJob::slotReadStandardOutput()
{
    mProcessOutputData += mProcess->readAllStandardOutput();
    // qDebug() << " mProcessOutputData " << mProcessOutputData;
}

QByteArray LMStudioStartProcessJob::processOutputData() const
{
    return mProcessOutputData;
}

#include "moc_lmstudiostartprocessjob.cpp"
