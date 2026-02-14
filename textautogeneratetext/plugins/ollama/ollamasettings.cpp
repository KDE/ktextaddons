/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamasettings.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <QDebug>
#include <QProcessEnvironment>

using namespace Qt::Literals::StringLiterals;
OllamaSettings::OllamaSettings() = default;

OllamaSettings::~OllamaSettings() = default;

QUrl OllamaSettings::serverUrl() const
{
    return mServerUrl;
}

void OllamaSettings::setServerUrl(const QUrl &newServerUrl)
{
    mServerUrl = newServerUrl;
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
    QProcessEnvironment environment;
    if (!mCudaVisibleDevice.isEmpty()) {
        environment.insert(u"CUDA_VISIBLE_DEVICES"_s, mCudaVisibleDevice);
    }
    if (!mVulkanSupport.isEmpty()) {
        environment.insert(u"OLLAMA_VULKAN"_s, mVulkanSupport);
    }
    if (!mRocrVisibleDevice.isEmpty()) {
        environment.insert(u"ROCR_VISIBLE_DEVICES"_s, mRocrVisibleDevice);
    }
    if (!mOverrideGfxVersion.isEmpty()) {
        environment.insert(u"HSA_OVERRIDE_GFX_VERSION"_s, mOverrideGfxVersion);
    }
    if (!mDefaultModelPath.isEmpty()) {
        environment.insert(u"OLLAMA_MODELS"_s, mDefaultModelPath);
    }
    // TODO add OLLAMA_ORIGINS/OLLAMA_HOST
    return environment;
}

QString OllamaSettings::defaultModelPath() const
{
    return mDefaultModelPath;
}

void OllamaSettings::setDefaultModelPath(const QString &newDefaultModelPath)
{
    mDefaultModelPath = newDefaultModelPath;
}

QDebug operator<<(QDebug d, const OllamaSettings &t)
{
    d.space() << "vulkanSupport:" << t.vulkanSupport();
    d.space() << "overrideGfxVersion:" << t.overrideGfxVersion();
    d.space() << "rocrVisibleDevice:" << t.rocrVisibleDevice();
    d.space() << "cudaVisibleDevice:" << t.cudaVisibleDevice();
    d.space() << "displayName:" << t.displayName();
    d.space() << "serverUrl:" << t.serverUrl();
    d.space() << "defaultModelPath:" << t.defaultModelPath();
    d.space() << "currentModel:" << t.currentModel();
    d.space() << "seed:" << t.seed();
    d.space() << "temperature:" << t.temperature();
    return d;
}

void OllamaSettings::load(const KConfigGroup &config)
{
    OllamaCommonSettings::load(config);
    if (config.hasKey(u"ServerUrl"_s)) {
        setServerUrl(config.readEntry(u"ServerUrl"_s, QUrl()));
    }
    setOverrideGfxVersion(config.readEntry(u"OverrideGfxVersion"_s));
    setVulkanSupport(config.readEntry(u"VulkanSupport"_s));
    setRocrVisibleDevice(config.readEntry(u"RocrVisibleDevice"_s));
    setCudaVisibleDevice(config.readEntry(u"CudaVisibleDevice"_s));
    setKeepAliveMinutes(config.readEntry(u"KeepAliveMinutes"_s, 1));
}

void OllamaSettings::save(KConfigGroup &config)
{
    config.writeEntry(u"ServerUrl"_s, serverUrl());
    config.writeEntry(u"OverrideGfxVersion"_s, overrideGfxVersion());
    config.writeEntry(u"VulkanSupport"_s, vulkanSupport());
    config.writeEntry(u"RocrVisibleDevice"_s, rocrVisibleDevice());
    config.writeEntry(u"CudaVisibleDevice"_s, cudaVisibleDevice());
}
