/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include "textautogenerateollama_export.h"

#include <QString>
#include <QUrl>
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

private:
    QString mDisplayName;
    QUrl mServerUrl = QUrl(u"http://127.0.0.1:11434"_s);
    QString mCurrentModel;
    int mSeed = 0;
    double mTemperature = 0.8;
};
