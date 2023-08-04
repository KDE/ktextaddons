/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotengineutils.h"

#include <KConfigGroup>
#include <KSharedConfig>

QString BergamotEngineUtils::defaultBergamotRepository()
{
    return QStringLiteral("https://translatelocally.com/models.json");
}

QString BergamotEngineUtils::groupName()
{
    return QStringLiteral("BergamotTranslator");
}

QString BergamotEngineUtils::coreNumberKey()
{
    return QStringLiteral("CoreNumber");
}

QString BergamotEngineUtils::memoryByThreadKey()
{
    return QStringLiteral("MemoryByThread");
}

void BergamotEngineUtils::SettingsInfo::loadSettingsInfo()
{
    KConfigGroup myGroup(KSharedConfig::openConfig(), BergamotEngineUtils::groupName());
    numberOfThread = myGroup.readEntry(BergamotEngineUtils::coreNumberKey(), 2);
    memoryByThread = myGroup.readEntry(BergamotEngineUtils::memoryByThreadKey(), 64);
}

void BergamotEngineUtils::SettingsInfo::saveSettingsInfo()
{
    KConfigGroup myGroup(KSharedConfig::openConfig(), BergamotEngineUtils::groupName());
    myGroup.writeEntry(BergamotEngineUtils::coreNumberKey(), numberOfThread);
    myGroup.writeEntry(BergamotEngineUtils::memoryByThreadKey(), memoryByThread);
    myGroup.sync();
}
