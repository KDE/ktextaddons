/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lingvaengineutil.h"
using namespace Qt::Literals::StringLiterals;

QString LingvaEngineUtil::groupName()
{
    return u"LingvaTranslator"_s;
}

QString LingvaEngineUtil::serverUrlKey()
{
    return u"ServerUrl"_s;
}

QString LingvaEngineUtil::defaultServerUrl()
{
    return u"https://lingva.ml"_s;
}
