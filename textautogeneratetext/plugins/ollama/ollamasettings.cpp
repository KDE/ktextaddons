/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamasettings.h"
#include <KLocalizedString>
#include <qprocess.h>

using namespace Qt::Literals::StringLiterals;
OllamaSettings::OllamaSettings()
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

QString OllamaSettings::rocrVisibleDevice() const
{
    return mRocrVisibleDevice;
}

void OllamaSettings::setRocrVisibleDevice(const QString &newRocrVisibleDevice)
{
    mRocrVisibleDevice = newRocrVisibleDevice;
}

QString OllamaSettings::cudaVisibleDevice() const
{
    return mCudaVisibleDevice;
}

void OllamaSettings::setCudaVisibleDevice(const QString &newCudaVisibleDevice)
{
    mCudaVisibleDevice = newCudaVisibleDevice;
}

QProcessEnvironment OllamaSettings::processEnvironment() const
{
    return {};
}
