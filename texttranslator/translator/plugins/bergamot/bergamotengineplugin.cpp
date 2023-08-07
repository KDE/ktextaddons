/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotengineplugin.h"
#include "bergamotmarianinterface.h"
#include "managermodeltranslator.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>

BergamotEnginePlugin::BergamotEnginePlugin(QObject *parent)
    : TextTranslator::TranslatorEnginePlugin(parent)
    , mBergamotInterface(new BergamotMarianInterface(this))
{
    loadSettings();
}

BergamotEnginePlugin::~BergamotEnginePlugin() = default;

void BergamotEnginePlugin::translate()
{
    mBergamotInterface->translate(inputText());
}

void BergamotEnginePlugin::loadSettings()
{
    mSettingsInfo.loadSettingsInfo();
    ManagerModelTranslator::self()->downloadListModels();
}
