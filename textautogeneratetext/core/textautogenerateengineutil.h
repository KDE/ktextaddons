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
[[nodiscard]] QString engineTranslateName(); // TODO remove
[[nodiscard]] QString defaultEngineName(); // TODO remove
[[nodiscard]] QString groupAutoGenerateTextName(); // TODO remove
[[nodiscard]] QString loadEngine();
[[nodiscard]] QString defaultConfigFileName();
};
}
