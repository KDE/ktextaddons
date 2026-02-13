/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollamacommon_export.h"

#include <QString>
#include <QUrl>
class QDebug;
class KConfigGroup;
class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonSettings
{
    Q_GADGET
public:
    enum class KeepAliveType : uint8_t {
        Unknown = 0,
        KeepAliveForever,
        UnloadAfterUse,
        SetTimer,
    };
    Q_ENUM(KeepAliveType)
    OllamaCommonSettings();
    virtual ~OllamaCommonSettings();

    [[nodiscard]] int seed() const;
    void setSeed(int newSeed);

    [[nodiscard]] double temperature() const;
    void setTemperature(double newTemperature);

    [[nodiscard]] QString currentModel() const;
    void setCurrentModel(const QString &newCurrentModel);

    [[nodiscard]] QString displayName() const;
    void setDisplayName(const QString &newName);

    [[nodiscard]] int keepAliveMinutes() const;
    void setKeepAliveMinutes(int newKeepAliveMinutes);

    virtual void load(const KConfigGroup &config);
    virtual void save(KConfigGroup &config);

    [[nodiscard]] OllamaCommonSettings::KeepAliveType keepAliveType() const;
    void setKeepAliveType(OllamaCommonSettings::KeepAliveType newKeepAliveType);

    [[nodiscard]] static QString convertKeepAliveTypeToString(OllamaCommonSettings::KeepAliveType type);
    [[nodiscard]] static OllamaCommonSettings::KeepAliveType convertKeepAliveTypeFromString(const QString &str);

private:
    QString mDisplayName;
    QString mCurrentModel;
    int mSeed = 0;
    double mTemperature = 0.8;
    int mKeepAliveMinutes = 1;
    OllamaCommonSettings::KeepAliveType mKeepAliveType = KeepAliveType::Unknown;
};
TEXTAUTOGENERATEOLLAMACOMMON_EXPORT QDebug operator<<(QDebug d, const OllamaCommonSettings &t);
