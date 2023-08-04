/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "bergamotengineplugin.h"
#include "bergamottranslator_debug.h"
#include <KLocalizedString>

BergamotEnginePlugin::BergamotEnginePlugin(QObject *parent)
    : TextTranslator::TranslatorEnginePlugin(parent)
{
}

BergamotEnginePlugin::~BergamotEnginePlugin() = default;

void BergamotEnginePlugin::translate()
{
}

void BergamotEnginePlugin::loadSettings()
{
    // TODO
}
