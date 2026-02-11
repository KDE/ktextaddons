/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "ollamacommonsettings.h"
#include "textautogenerateollama_export.h"
#include <QString>
#include <QUrl>
class QDebug;
class QProcessEnvironment;
using namespace Qt::Literals::StringLiterals;
class TEXTAUTOGENERATEOLLAMA_EXPORT OllamaSettings : public OllamaCommonSettings
{
public:
    OllamaSettings();
    ~OllamaSettings();

    [[nodiscard]] QUrl serverUrl() const;
    void setServerUrl(const QUrl &newServerUrl);

    [[nodiscard]] QString overrideGfxVersion() const;
    void setOverrideGfxVersion(const QString &newOverrideGfxVersion);

    [[nodiscard]] QString vulkanSupport() const;
    void setVulkanSupport(const QString &newVulkanSupport);

    [[nodiscard]] QString rocrVisibleDevice() const;
    void setRocrVisibleDevice(const QString &newRocrVisibleDevice);

    [[nodiscard]] QString cudaVisibleDevice() const;
    void setCudaVisibleDevice(const QString &newCudaVisibleDevice);

    [[nodiscard]] QProcessEnvironment processEnvironment() const;

    [[nodiscard]] QString defaultModelPath() const;
    void setDefaultModelPath(const QString &newDefaultModelPath);

private:
    QString mVulkanSupport;
    QString mOverrideGfxVersion;
    QString mRocrVisibleDevice;
    QString mCudaVisibleDevice;
    QString mDisplayName;
    QUrl mServerUrl = QUrl(u"http://127.0.0.1:11434"_s);
    QString mDefaultModelPath;
};
TEXTAUTOGENERATEOLLAMA_EXPORT QDebug operator<<(QDebug d, const OllamaSettings &t);
