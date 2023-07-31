/*
   SPDX-FileCopyrightText: 2023 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/

#pragma once

#include "textutils_export.h"
#include <QChar>
#include <QStringView>
namespace TextUtils
{
namespace ConvertText
{
Q_REQUIRED_RESULT TEXTUTILS_EXPORT QString normalize(QStringView str);
}
}
