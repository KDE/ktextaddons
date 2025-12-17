/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamastartprocessjob.h"
#include "autogeneratetext_ollama_debug.h"
#include <KLocalizedString>
#include <TextAddonsWidgets/ExecutableUtils>
using namespace Qt::Literals::StringLiterals;
OllamaStartProcessJob::OllamaStartProcessJob(QObject *parent)
    : QObject{parent}
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
    // TODO
    deleteLater();
}

#include "moc_ollamastartprocessjob.cpp"
