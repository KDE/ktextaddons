/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamasettings.h"
#include <KUser>

OllamaSettings::OllamaSettings()
{
    mServerUrl = QUrl(QStringLiteral("http://127.0.0.1:11434"));
    KUser user;
    mSystemPrompt = QStringLiteral(
                        "You are an AI assistant. You are speaking to a person named %1. "
                        "Be helpful, professional, and courteous. Do not give inaccurate "
                        "information.")
                        .arg(user.property(KUser::UserProperty::FullName).toString());
}

OllamaSettings::~OllamaSettings() = default;

int OllamaSettings::seed() const
{
    return mSeed;
}

void OllamaSettings::setSeed(int newSeed)
{
    mSeed = newSeed;
}

double OllamaSettings::temperature() const
{
    return mTemperature;
}

void OllamaSettings::setTemperature(double newTemperature)
{
    mTemperature = newTemperature;
}

QString OllamaSettings::currentModel() const
{
    return mCurrentModel;
}

void OllamaSettings::setCurrentModel(const QString &newCurrentModel)
{
    mCurrentModel = newCurrentModel;
}

QUrl OllamaSettings::serverUrl() const
{
    return mServerUrl;
}

void OllamaSettings::setServerUrl(const QUrl &newServerUrl)
{
    mServerUrl = newServerUrl;
}

QString OllamaSettings::systemPrompt() const
{
    return mSystemPrompt;
}

void OllamaSettings::setSystemPrompt(const QString &newSystemPrompt)
{
    mSystemPrompt = newSystemPrompt;
}
