/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lmstudiosettings.h"

#include <KConfigGroup>
#include <KLocalizedString>
#include <QDebug>
#include <QProcessEnvironment>

using namespace Qt::Literals::StringLiterals;

LMStudioSettings::LMStudioSettings() = default;

LMStudioSettings::~LMStudioSettings() = default;

QString LMStudioSettings::displayName() const
{
    return mDisplayName;
}

void LMStudioSettings::setDisplayName(const QString &newName)
{
    mDisplayName = newName;
}

QString LMStudioSettings::currentModel() const
{
    return mCurrentModel;
}

void LMStudioSettings::setCurrentModel(const QString &newCurrentModel)
{
    mCurrentModel = newCurrentModel;
}

QDebug operator<<(QDebug d, const LMStudioSettings &t)
{
    d.space() << "displayName:" << t.displayName();
    d.space() << "serverUrl:" << t.serverUrl();
    d.space() << "currentModel:" << t.currentModel();
    return d;
}

void LMStudioSettings::load(const KConfigGroup &config)
{
    setDisplayName(config.readEntry(u"Name"_s));
    if (config.hasKey(u"ServerUrl"_s)) {
        setServerUrl(config.readEntry(u"ServerUrl"_s, QUrl()));
    }
    setCurrentModel(config.readEntry(u"CurrentModel"_s));
}

void LMStudioSettings::save(KConfigGroup &config)
{
    config.writeEntry(u"Name"_s, displayName());
    config.writeEntry(u"ServerUrl"_s, serverUrl());
    config.writeEntry(u"CurrentModel"_s, currentModel());
}

QUrl LMStudioSettings::serverUrl() const
{
    return mServerUrl;
}

void LMStudioSettings::setServerUrl(const QUrl &newServerUrl)
{
    mServerUrl = newServerUrl;
}

QUrl LMStudioSettings::defaultServerUrl() const
{
    return QUrl(u"http://127.0.0.1:1234"_s);
}

bool LMStudioSettings::defaultThoughtProcessing() const
{
    return false;
}

bool LMStudioSettings::operator==(const LMStudioSettings &other) const
{
    return other.mDisplayName == mDisplayName && other.mCurrentModel == mCurrentModel && other.mServerUrl == mServerUrl
        && mShareNameType == other.mShareNameType && mThoughtProcessing == other.mThoughtProcessing;
}

#include "moc_lmstudiosettings.cpp"
