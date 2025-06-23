/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "deeplengineutil.h"
using namespace Qt::Literals::StringLiterals;

QString DeeplEngineUtil::groupName()
{
    return u"DeepLTranslator"_s;
}

QString DeeplEngineUtil::freeLicenseKey()
{
    return u"freeLicense"_s;
}

QString DeeplEngineUtil::apiGroupName()
{
    return u"apiKey"_s;
}

QString DeeplEngineUtil::translatorGroupName()
{
    return u"DeepL"_s;
}
