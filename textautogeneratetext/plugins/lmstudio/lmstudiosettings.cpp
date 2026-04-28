/*
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
    return mDisplayName;
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

bool LMStudioSettings::thoughtProcessing() const
{
    return mThoughtProcessing;
}

QUrl LMStudioSettings::defaultServerUrl() const
{
    return QUrl(u"http://127.0.0.1:1234"_s);
}

void LMStudioSettings::setThoughtProcessing(bool newThoughtProcessing)
{
    mThoughtProcessing = newThoughtProcessing;
}

bool LMStudioSettings::defaultThoughtProcessing() const
{
    return false;
}

QString LMStudioSettings::convertShareNameTypeToString(LMStudioSettings::ShareNameType type)
{
    switch (type) {
    case ShareNameType::DoNotShare:
        return u"DoNotShare"_s;
    case ShareNameType::UserName:
        return u"UserName"_s;
    case ShareNameType::FullName:
        return u"FullName"_s;
    }

    return {};
}

LMStudioSettings::ShareNameType LMStudioSettings::convertShareNameTypeFromString(const QString &str)
{
    if (str == "DoNotShare"_L1) {
        return LMStudioSettings::ShareNameType::DoNotShare;
    } else if (str == "UserName"_L1) {
        return LMStudioSettings::ShareNameType::UserName;
    } else if (str == "FullName"_L1) {
        return LMStudioSettings::ShareNameType::FullName;
    }
    return LMStudioSettings::ShareNameType::DoNotShare;
}

LMStudioSettings::ShareNameType LMStudioSettings::shareNameType() const
{
    return mShareNameType;
}

void LMStudioSettings::setShareNameType(const LMStudioSettings::ShareNameType &newShareNameType)
{
    mShareNameType = newShareNameType;
}

LMStudioSettings::ShareNameType LMStudioSettings::defaultShareNameType() const
{
    return LMStudioSettings::ShareNameType::DoNotShare;
}

bool LMStudioSettings::operator==(const LMStudioSettings &other) const
{
    return other.mDisplayName == mDisplayName && other.mCurrentModel == mCurrentModel && other.mServerUrl == mServerUrl
        && mShareNameType == other.mShareNameType && mThoughtProcessing == other.mThoughtProcessing;
}
