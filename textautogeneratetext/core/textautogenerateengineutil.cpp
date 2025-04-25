/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateengineutil.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
using namespace TextAutogenerateText;
using namespace Qt::Literals::StringLiterals;
QString TextAutogenerateEngineUtil::engineTranslateName()
{
    return i18n("Ollama");
}

QString TextAutogenerateEngineUtil::defaultEngineName()
{
    return "ollama"_L1;
}

QString TextAutogenerateEngineUtil::groupAutoGenerateTextName()
{
    return "AutoGenerateText"_L1;
}

QString TextAutogenerateEngineUtil::loadEngine()
{
    KConfigGroup myGeneralGroup(KSharedConfig::openConfig(), groupAutoGenerateTextName());
    const QString engineTypeStr = myGeneralGroup.readEntry(engineTranslateName(), defaultEngineName()); // Default ollama
    return engineTypeStr;
}

QString TextAutogenerateEngineUtil::defaultConfigFileName()
{
    return QStringLiteral("textautogeneraterc");
}
