/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaonlinesettings.h"
#include <KLocalizedString>
#include <QDebug>

using namespace Qt::Literals::StringLiterals;
OllamaOnlineSettings::OllamaOnlineSettings() = default;

OllamaOnlineSettings::~OllamaOnlineSettings() = default;

QUrl OllamaOnlineSettings::serverUrl() const
{
    return mServerUrl;
}

void OllamaOnlineSettings::setServerUrl(const QUrl &newServerUrl)
{
    mServerUrl = newServerUrl;
}

QDebug operator<<(QDebug d, const OllamaOnlineSettings &t)
{
    d.space() << "displayName:" << t.displayName();
    d.space() << "serverUrl:" << t.serverUrl();
    d.space() << "currentModel:" << t.currentModel();
    return d;
}
