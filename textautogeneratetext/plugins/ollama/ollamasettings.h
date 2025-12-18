/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollama_export.h"

#include <QString>
#include <QUrl>
class QProcessEnvironment;
using namespace Qt::Literals::StringLiterals;
class TEXTAUTOGENERATEOLLAMA_EXPORT OllamaSettings
{
public:
    OllamaSettings();
    ~OllamaSettings();
    [[nodiscard]] int seed() const;
    void setSeed(int newSeed);

    [[nodiscard]] double temperature() const;
    void setTemperature(double newTemperature);

    [[nodiscard]] QString currentModel() const;
    void setCurrentModel(const QString &newCurrentModel);

    [[nodiscard]] QUrl serverUrl() const;
    void setServerUrl(const QUrl &newServerUrl);

    [[nodiscard]] QString displayName() const;
    void setDisplayName(const QString &newName);

    [[nodiscard]] QString overrideGfxVersion() const;
    void setOverrideGfxVersion(const QString &newOverrideGfxVersion);

    [[nodiscard]] QString vulkanSupport() const;
    void setVulkanSupport(const QString &newVulkanSupport);

    [[nodiscard]] QString rocrVisibleDevice() const;
    void setRocrVisibleDevice(const QString &newRocrVisibleDevice);

    [[nodiscard]] QString cudaVisibleDevice() const;
    void setCudaVisibleDevice(const QString &newCudaVisibleDevice);

    [[nodiscard]] QProcessEnvironment processEnvironment() const;

private:
    QString mVulkanSupport;
    QString mOverrideGfxVersion;
    QString mRocrVisibleDevice;
    QString mCudaVisibleDevice;
    QString mDisplayName;
    QUrl mServerUrl = QUrl(u"http://127.0.0.1:11434"_s);
    QString mCurrentModel;
    int mSeed = 0;
    double mTemperature = 0.8;
};
