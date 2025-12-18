/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

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

OllamaStartProcessJob::~OllamaStartProcessJob() = default;

void OllamaStartProcessJob::start()
{
    const QString ollamaPath = TextAddonsWidgets::ExecutableUtils::findExecutable(u"ollama"_s);
    if (ollamaPath.isEmpty()) {
        qCWarning(AUTOGENERATETEXT_OLLAMA_LOG) << "Ollama doesn't exist";
        Q_EMIT ollamaFailed(i18n("Ollama not found on system."));
        deleteLater();
        return;
    }
    if (!mOllamaManager) {
        qCWarning(AUTOGENERATETEXT_OLLAMA_LOG) << "OllamaManager is not defined";
        Q_EMIT ollamaFailed(i18n("Impossible to start Ollama."));
        deleteLater();
        return;
    }

    auto process = new QProcess(this);
    process->setProgram(ollamaPath);
    process->setArguments({u"start"_s});
    process->setProcessEnvironment(mOllamaManager->ollamaSettings()->processEnvironment());

    if (process->startDetached()) {
        Q_EMIT ollamaStarted();
    } else {
        qCWarning(AUTOGENERATETEXT_OLLAMA_LOG) << "Impossible to start ollama";
        Q_EMIT ollamaFailed(i18n("Impossible to start Ollama."));
    }
    deleteLater();
}

#include "moc_ollamastartprocessjob.cpp"
