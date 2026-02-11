/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollamacommon_export.h"

#include <QString>
#include <QUrl>
class QDebug;
class TEXTAUTOGENERATEOLLAMACOMMON_EXPORT OllamaCommonSettings
{
public:
    OllamaCommonSettings();
    ~OllamaCommonSettings();

    [[nodiscard]] int seed() const;
    void setSeed(int newSeed);

    [[nodiscard]] double temperature() const;
    void setTemperature(double newTemperature);

    [[nodiscard]] QString currentModel() const;
    void setCurrentModel(const QString &newCurrentModel);

    [[nodiscard]] QString displayName() const;
    void setDisplayName(const QString &newName);

private:
    QString mDisplayName;
    QString mCurrentModel;
    int mSeed = 0;
    double mTemperature = 0.8;
};
TEXTAUTOGENERATEOLLAMACOMMON_EXPORT QDebug operator<<(QDebug d, const OllamaCommonSettings &t);
