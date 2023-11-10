/*
  SPDX-FileCopyrightText: 2022-2023 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <QString>

namespace LibreTranslateEngineUtil
{
[[nodiscard]] QString groupName();
[[nodiscard]] QString serverUrlKey();
[[nodiscard]] QString defaultServerUrl();
[[nodiscard]] QString serverRequiredApiKey();
[[nodiscard]] QString adaptUrl(QString serverUrl);
[[nodiscard]] QString apiGroupName();
[[nodiscard]] QString translatorGroupName();
};
