/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamacommonsettings.h"
#include <QDebug>

using namespace Qt::Literals::StringLiterals;
OllamaCommonSettings::OllamaCommonSettings() = default;

OllamaCommonSettings::~OllamaCommonSettings() = default;

QString OllamaCommonSettings::currentModel() const
{
    return mCurrentModel;
}

void OllamaCommonSettings::setCurrentModel(const QString &newCurrentModel)
{
    mCurrentModel = newCurrentModel;
}

int OllamaCommonSettings::seed() const
{
    return mSeed;
}

void OllamaCommonSettings::setSeed(int newSeed)
{
    mSeed = newSeed;
}

double OllamaCommonSettings::temperature() const
{
    return mTemperature;
}

void OllamaCommonSettings::setTemperature(double newTemperature)
{
    mTemperature = newTemperature;
}
QString OllamaCommonSettings::displayName() const
{
    return mDisplayName;
}

void OllamaCommonSettings::setDisplayName(const QString &newName)
{
    mDisplayName = newName;
}

QDebug operator<<(QDebug d, const OllamaCommonSettings &t)
{
    d.space() << "displayName:" << t.displayName();
    d.space() << "currentModel:" << t.currentModel();
    d.space() << "temperature:" << t.temperature();
    d.space() << "seed:" << t.seed();
    return d;
}
