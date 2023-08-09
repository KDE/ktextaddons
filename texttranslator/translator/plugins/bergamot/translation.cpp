/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later

  Based on translateLocally code
*/

#include "translation.h"
#include <bergamot-translator/src/translator/response.h>

Translation::Translation()
    : mResponse(nullptr)
{
}

Translation::Translation(marian::bergamot::Response &&response)
    : mResponse(std::make_shared<marian::bergamot::Response>(std::move(response)))
{
}

QString Translation::translation() const
{
    return QString::fromStdString(mResponse->target.text);
}
