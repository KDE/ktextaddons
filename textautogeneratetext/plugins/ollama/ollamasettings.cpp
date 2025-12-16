/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamasettings.h"
using namespace Qt::Literals::StringLiterals;

#include <KLocalizedString>

OllamaSettings::OllamaSettings()
    : mServerUrl(QUrl(u"http://127.0.0.1:11434"_s))
{
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

QString OllamaSettings::displayName() const
{
    return mDisplayName;
}

void OllamaSettings::setDisplayName(const QString &newName)
{
    mDisplayName = newName;
}

QString OllamaSettings::overrideGfxVersion() const
{
    return mOverrideGfxVersion;
}

void OllamaSettings::setOverrideGfxVersion(const QString &newOverrideGfxVersion)
{
    mOverrideGfxVersion = newOverrideGfxVersion;
}

QString OllamaSettings::vulkanSupport() const
{
    return mVulkanSupport;
}

void OllamaSettings::setVulkanSupport(const QString &newVulkanSupport)
{
    mVulkanSupport = newVulkanSupport;
}
