/*
  SPDX-FileCopyrightText: 2023-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QString>
namespace TextSpeechToText
{
namespace TextSpeechToTextUtil
{
[[nodiscard]] QString groupTranslateName();
[[nodiscard]] QString engineTextToSpeechName();
[[nodiscard]] QString defaultEngineName();
[[nodiscard]] QString soundGroupName();

/*!
 * \brief Returns the engine name stored in the configuration, or defaultEngineName() when none was selected yet.
 */
[[nodiscard]] QString loadEngineName();

/*!
 * \brief Stores \a engineName as the engine to use.
 */
void saveEngineName(const QString &engineName);
}
}
