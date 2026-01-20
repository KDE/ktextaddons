/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamacloudsettings.h"
#include <KLocalizedString>
#include <QDebug>

using namespace Qt::Literals::StringLiterals;
OllamaCloudSettings::OllamaCloudSettings() = default;

OllamaCloudSettings::~OllamaCloudSettings() = default;

QString OllamaCloudSettings::currentModel() const
{
    return mCurrentModel;
}

void OllamaCloudSettings::setCurrentModel(const QString &newCurrentModel)
{
    mCurrentModel = newCurrentModel;
}

QUrl OllamaCloudSettings::serverUrl() const
{
    return mServerUrl;
}

void OllamaCloudSettings::setServerUrl(const QUrl &newServerUrl)
{
    mServerUrl = newServerUrl;
}

QString OllamaCloudSettings::displayName() const
{
    return mDisplayName;
}

void OllamaCloudSettings::setDisplayName(const QString &newName)
{
    mDisplayName = newName;
}

QDebug operator<<(QDebug d, const OllamaCloudSettings &t)
{
    d.space() << "displayName:" << t.displayName();
    d.space() << "serverUrl:" << t.serverUrl();
    d.space() << "currentModel:" << t.currentModel();
    return d;
}
