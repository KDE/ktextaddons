/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogenerateengineutil.h"

using namespace TextAutogenerateText;
using namespace Qt::Literals::StringLiterals;
QString TextAutogenerateEngineUtil::engineTranslateName()
{
    return {};
}

QString TextAutogenerateEngineUtil::defaultEngineName()
{
    return "ollama"_L1;
}
