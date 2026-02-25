/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamacommonsettings.h"
#include <KConfigGroup>
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

int OllamaCommonSettings::keepAliveMinutes() const
{
    return mKeepAliveMinutes;
}

void OllamaCommonSettings::setKeepAliveMinutes(int newKeepAliveMinutes)
{
    mKeepAliveMinutes = newKeepAliveMinutes;
}

double OllamaCommonSettings::defaultTemperature() const
{
    return 0.8;
}

int OllamaCommonSettings::defaultSeed() const
{
    return 0;
}

int OllamaCommonSettings::defaultKeepAliveMinutes() const
{
    return 1;
}

qint64 OllamaCommonSettings::defaultContextWindowSize() const
{
    return 16384;
}

bool OllamaCommonSettings::defaultThoughtProcessing() const
{
    return false;
}

OllamaCommonSettings::KeepAliveType OllamaCommonSettings::defaultKeepAliveType() const
{
    return OllamaCommonSettings::KeepAliveType::UnloadAfterUse;
}

OllamaCommonSettings::ShareNameType OllamaCommonSettings::defaultShareNameType() const
{
    return OllamaCommonSettings::ShareNameType::DoNotShare;
}

void OllamaCommonSettings::load(const KConfigGroup &config)
{
    setDisplayName(config.readEntry(u"Name"_s));
    if (config.hasKey(u"Temperature"_s)) {
        setTemperature(config.readEntry(u"Temperature"_s, defaultTemperature()));
    }
    setSeed(config.readEntry(u"Seed"_s, defaultSeed()));
    setCurrentModel(config.readEntry(u"CurrentModel"_s));
    setKeepAliveMinutes(config.readEntry(u"KeepAliveMinutes"_s, defaultKeepAliveMinutes()));
    setContextWindowSize(config.readEntry(u"ContextWindowSize"_s, defaultContextWindowSize()));
    setThoughtProcessing(config.readEntry(u"ThoughtProcessing"_s, defaultThoughtProcessing()));
    setKeepAliveType(OllamaCommonSettings::convertKeepAliveTypeFromString(
        config.readEntry(u"KeepAliveType"_s, OllamaCommonSettings::convertKeepAliveTypeToString(defaultKeepAliveType()))));
    setShareNameType(OllamaCommonSettings::convertShareNameTypeFromString(
        config.readEntry(u"ShareName"_s, OllamaCommonSettings::convertShareNameTypeToString(defaultShareNameType()))));
}

void OllamaCommonSettings::save(KConfigGroup &config)
{
    config.writeEntry(u"Name"_s, displayName());
    config.writeEntry(u"CurrentModel"_s, currentModel());
    config.writeEntry(u"Seed"_s, seed());
    config.writeEntry(u"Temperature"_s, temperature());
    config.writeEntry(u"KeepAliveMinutes"_s, keepAliveMinutes());
    config.writeEntry(u"ContextWindowSize"_s, contextWindowSize());
    config.writeEntry(u"KeepAliveType"_s, OllamaCommonSettings::convertKeepAliveTypeToString(KeepAliveType()));
    config.writeEntry(u"ThoughtProcessing"_s, thoughtProcessing());
    config.writeEntry(u"ShareName"_s, OllamaCommonSettings::convertShareNameTypeToString(shareNameType()));
}

OllamaCommonSettings::KeepAliveType OllamaCommonSettings::keepAliveType() const
{
    return mKeepAliveType;
}

void OllamaCommonSettings::setKeepAliveType(OllamaCommonSettings::KeepAliveType newKeepAliveType)
{
    mKeepAliveType = newKeepAliveType;
}

QDebug operator<<(QDebug d, const OllamaCommonSettings &t)
{
    d.space() << "displayName:" << t.displayName();
    d.space() << "currentModel:" << t.currentModel();
    d.space() << "temperature:" << t.temperature();
    d.space() << "seed:" << t.seed();
    d.space() << "keepAliveMinutes:" << t.keepAliveMinutes();
    d.space() << "keepAliveType:" << t.keepAliveType();
    d.space() << "contextWindowSize:" << t.contextWindowSize();
    d.space() << "thoughtProcessing:" << t.thoughtProcessing();
    d.space() << "shareNameType:" << t.shareNameType();
    return d;
}

QString OllamaCommonSettings::convertKeepAliveTypeToString(OllamaCommonSettings::KeepAliveType type)
{
    switch (type) {
    case KeepAliveType::Unknown:
        break;
    case KeepAliveType::KeepAliveForever:
        return u"KeepAliveForever"_s;
    case KeepAliveType::UnloadAfterUse:
        return u"UnloadAfterUse"_s;
    case KeepAliveType::SetTimer:
        return u"SetTimer"_s;
    }

    return {};
}

OllamaCommonSettings::KeepAliveType OllamaCommonSettings::convertKeepAliveTypeFromString(const QString &str)
{
    if (str == "KeepAliveForever"_L1) {
        return OllamaCommonSettings::KeepAliveType::KeepAliveForever;
    } else if (str == "UnloadAfterUse"_L1) {
        return OllamaCommonSettings::KeepAliveType::UnloadAfterUse;
    } else if (str == "SetTimer"_L1) {
        return OllamaCommonSettings::KeepAliveType::SetTimer;
    }
    return OllamaCommonSettings::KeepAliveType::Unknown;
}

QString OllamaCommonSettings::convertShareNameTypeToString(OllamaCommonSettings::ShareNameType type)
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

OllamaCommonSettings::ShareNameType OllamaCommonSettings::shareNameType() const
{
    return mShareNameType;
}

void OllamaCommonSettings::setShareNameType(const OllamaCommonSettings::ShareNameType &newShareNameType)
{
    mShareNameType = newShareNameType;
}

OllamaCommonSettings::ShareNameType OllamaCommonSettings::convertShareNameTypeFromString(const QString &str)
{
    if (str == "DoNotShare"_L1) {
        return OllamaCommonSettings::ShareNameType::DoNotShare;
    } else if (str == "UserName"_L1) {
        return OllamaCommonSettings::ShareNameType::UserName;
    } else if (str == "FullName"_L1) {
        return OllamaCommonSettings::ShareNameType::FullName;
    }
    return OllamaCommonSettings::ShareNameType::DoNotShare;
}

qint64 OllamaCommonSettings::contextWindowSize() const
{
    return mContextWindowSize;
}

void OllamaCommonSettings::setContextWindowSize(qint64 newContextWindowSize)
{
    mContextWindowSize = newContextWindowSize;
}

bool OllamaCommonSettings::thoughtProcessing() const
{
    return mThoughtProcessing;
}

void OllamaCommonSettings::setThoughtProcessing(bool newThoughtProcessing)
{
    mThoughtProcessing = newThoughtProcessing;
}

#include "moc_ollamacommonsettings.cpp"
