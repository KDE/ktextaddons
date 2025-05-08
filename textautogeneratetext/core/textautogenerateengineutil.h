/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once
#include <QString>
namespace TextAutoGenerateText
{
namespace TextAutoGenerateEngineUtil
{
[[nodiscard]] QString engineTranslateName();
[[nodiscard]] QString defaultEngineName();
[[nodiscard]] QString groupAutoGenerateTextName();
[[nodiscard]] QString loadEngine();
[[nodiscard]] QString defaultConfigFileName();
};
}
