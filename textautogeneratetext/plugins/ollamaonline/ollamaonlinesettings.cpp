/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaonlinesettings.h"
#include <KConfigGroup>
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

void OllamaOnlineSettings::load(const KConfigGroup &config)
{
    OllamaCommonSettings::load(config);
    if (config.hasKey(u"ServerUrl"_s)) {
        setServerUrl(config.readEntry(u"ServerUrl"_s, QUrl()));
    }
}

void OllamaOnlineSettings::save(KConfigGroup &config)
{
    OllamaCommonSettings::save(config);
    config.writeEntry(u"ServerUrl"_s, serverUrl());
}
