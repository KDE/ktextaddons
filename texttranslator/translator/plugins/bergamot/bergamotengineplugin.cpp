/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotengineplugin.h"
#include "managermodeltranslator.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>

BergamotEnginePlugin::BergamotEnginePlugin(QObject *parent)
    : TextTranslator::TranslatorEnginePlugin(parent)
{
    loadSettings();
}

BergamotEnginePlugin::~BergamotEnginePlugin() = default;

void BergamotEnginePlugin::translate()
{
}

void BergamotEnginePlugin::loadSettings()
{
    mSettingsInfo.loadSettingsInfo();
    ManagerModelTranslator::self()->downloadListModels();
}
