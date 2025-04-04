/*
  SPDX-FileCopyrightText: 2022-2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "deeplengineutil.h"

QString DeeplEngineUtil::groupName()
{
    return QStringLiteral("DeepLTranslator");
}

QString DeeplEngineUtil::freeLicenseKey()
{
    return QStringLiteral("freeLicense");
}

QString DeeplEngineUtil::apiGroupName()
{
    return QStringLiteral("apiKey");
}

QString DeeplEngineUtil::translatorGroupName()
{
    return QStringLiteral("DeepL");
}
