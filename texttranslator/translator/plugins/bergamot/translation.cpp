/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later

  Based on translateLocally code
*/

#include "translation.h"
#include <slimt/Response.hh>

Translation::Translation()
    : mResponse(nullptr)
{
}

Translation::Translation(slimt::Response &&response)
    : mResponse(std::make_shared<slimt::Response>(std::move(response)))
{
}

QString Translation::translation() const
{
    return QString::fromStdString(mResponse->target.text);
}
