/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "libretranslateengineutil.h"
using namespace Qt::Literals::StringLiterals;

QString LibreTranslateEngineUtil::groupName()
{
    return u"LibreTranslateTranslator"_s;
}

QString LibreTranslateEngineUtil::serverUrlKey()
{
    return u"ServerUrl"_s;
}

QString LibreTranslateEngineUtil::translatorGroupName()
{
    return u"LibreTranslate"_s;
}

QString LibreTranslateEngineUtil::serverRequiredApiKey()
{
    return u"RequiredApiKey"_s;
}

QString LibreTranslateEngineUtil::defaultServerUrl()
{
    return u"https://libretranslate.com"_s;
}

QString LibreTranslateEngineUtil::adaptUrl(QString serverUrl)
{
    if (!serverUrl.startsWith(u"https://"_s) && !serverUrl.startsWith(u"http://"_s)) {
        serverUrl.prepend(u"https://"_s); // Add https:// by default
    }
    return serverUrl;
}

QString LibreTranslateEngineUtil::apiGroupName()
{
    return u"apiKey"_s;
}
