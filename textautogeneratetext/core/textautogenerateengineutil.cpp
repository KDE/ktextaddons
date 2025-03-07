/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateengineutil.h"
#include <KLocalizedString>
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
