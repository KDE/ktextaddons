/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "lmstudiocommonutils.h"
using namespace Qt::Literals::StringLiterals;

QString LMStudioCommonUtils::responsesPath()
{
    return u"/api/responses"_s;
}

QString LMStudioCommonUtils::modelsPath()
{
    return u"/api/v1/models"_s;
}
