/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamastartprocessjob.h"
#include "autogeneratetext_ollama_debug.h"
#include "ollamamanager.h"
#include "ollamasettings.h"
#include <KLocalizedString>
#include <QProcess>
#include <TextAddonsWidgets/ExecutableUtils>

using namespace Qt::Literals::StringLiterals;
OllamaStartProcessJob::OllamaStartProcessJob(OllamaManager *manager, QObject *parent)
    : QObject{parent}
    , mOllamaManager(manager)
{
}

OllamaStartProcessJob::~OllamaStartProcessJob()
{
    if (mProcess) {
        mProcess->kill();
        mProcess->deleteLater();
    }
}

bool OllamaStartProcessJob::start()
{
    const QString ollamaPath = TextAddonsWidgets::ExecutableUtils::findExecutable(u"ollama"_s);
    if (ollamaPath.isEmpty()) {
        qCWarning(AUTOGENERATETEXT_OLLAMA_LOG) << "Ollama doesn't exist";
        Q_EMIT ollamaFailed(i18n("Ollama not found on system."));
        deleteLater();
        return false;
    }
    if (!mOllamaManager) {
        qCWarning(AUTOGENERATETEXT_OLLAMA_LOG) << "OllamaManager is not defined";
        Q_EMIT ollamaFailed(i18n("Impossible to start Ollama."));
        deleteLater();
        return false;
    }

    mProcess = new QProcess(this);
    mProcess->setProgram(ollamaPath);
    mProcess->setArguments({u"start"_s});
    QProcessEnvironment envs = QProcessEnvironment::systemEnvironment();
    envs.insert(mOllamaManager->ollamaSettings()->processEnvironment());
    mProcess->setProcessEnvironment(envs);
    connect(mProcess, &QProcess::readyReadStandardOutput, this, &OllamaStartProcessJob::slotReadStandardOutput);
    connect(mProcess, &QProcess::readyReadStandardError, this, &OllamaStartProcessJob::slotReadStandardOutput);
    mProcess->start();
    if (mProcess->waitForStarted()) {
        Q_EMIT ollamaStarted();
    } else {
        qCWarning(AUTOGENERATETEXT_OLLAMA_LOG) << "Impossible to start ollama";
        Q_EMIT ollamaFailed(i18n("Impossible to start Ollama."));
        deleteLater();
        return false;
    }
    return true;
}

void OllamaStartProcessJob::slotReadStandardOutput()
{
    mProcessOutputData += mProcess->readAllStandardOutput();
    // qDebug() << " mProcessOutputData " << mProcessOutputData;
}

QByteArray OllamaStartProcessJob::processOutputData() const
{
    return mProcessOutputData;
}

#include "moc_ollamastartprocessjob.cpp"
