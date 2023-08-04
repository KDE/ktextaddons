/*
  SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "libbergamot_export.h"
#include <QString>

namespace BergamotEngineUtils
{
Q_REQUIRED_RESULT LIBBERGAMOT_EXPORT QString defaultBergamotRepository();
Q_REQUIRED_RESULT LIBBERGAMOT_EXPORT QString groupName();
};