/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateengineutil.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
QString TextAutoGenerateEngineUtil::engineTranslateName()
{
    return i18n("Ollama");
}

QString TextAutoGenerateEngineUtil::defaultEngineName()
{
    return "ollama"_L1;
}

QString TextAutoGenerateEngineUtil::groupAutoGenerateTextName()
{
    return "AutoGenerateText"_L1;
}

QString TextAutoGenerateEngineUtil::loadEngine()
{
    KConfigGroup myGeneralGroup(KSharedConfig::openConfig(), groupAutoGenerateTextName());
    const QString engineTypeStr = myGeneralGroup.readEntry(engineTranslateName(), defaultEngineName()); // Default ollama
    return engineTypeStr;
}

QString TextAutoGenerateEngineUtil::defaultConfigFileName()
{
    return QStringLiteral("textautogeneraterc");
}
