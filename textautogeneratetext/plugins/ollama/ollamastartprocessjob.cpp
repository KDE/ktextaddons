/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamastartprocessjob.h"
#include "autogeneratetext_ollama_debug.h"
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

    const bool status = QProcess::startDetached(ollamaPath, {u"start"_s});
    if (!status) {
        qCWarning(AUTOGENERATETEXT_OLLAMA_LOG) << "Impossible to start ollama";
        Q_EMIT ollamaFailed(i18n("Impossible to start Ollama."));
    } else {
        Q_EMIT ollamaStarted();
    }
    deleteLater();
}

#include "moc_ollamastartprocessjob.cpp"
