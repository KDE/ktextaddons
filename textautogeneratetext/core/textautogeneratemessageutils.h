/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QString>

namespace TextAutoGenerateText
{
namespace TextAutoGenerateMessageUtils
{
[[nodiscard]] QString convertTextToHtml(const QString &str, const QString &searchedText = QString());
}
};
