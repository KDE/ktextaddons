/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetext_export.h"
#include <KSharedConfig>
#include <QString>
namespace TextAutoGenerateText
{
namespace TextAutoGenerateTextUtils
{
/*!
 */
[[nodiscard]] TEXTAUTOGENERATETEXT_EXPORT QString instanceConfigFileName();
/*!
 */
[[nodiscard]] TEXTAUTOGENERATETEXT_EXPORT QStringList instancesList(const KSharedConfig::Ptr &config);
/*!
 */
[[nodiscard]] TEXTAUTOGENERATETEXT_EXPORT QByteArray generateUUid();

/*!
 * \brief promptConfigFileName
 * \return
 */
[[nodiscard]] TEXTAUTOGENERATETEXT_EXPORT QString promptConfigFileName();

/*!
 * \brief promptsList
 * \param config
 * \return
 */
[[nodiscard]] TEXTAUTOGENERATETEXT_EXPORT QStringList promptsList(const KSharedConfig::Ptr &config);

/*!
 * \brief skillConfigFileName
 * \return
 */
[[nodiscard]] TEXTAUTOGENERATETEXT_EXPORT QString skillConfigFileName();

/*!
 * \brief skillsList
 * \param config
 * \return
 */
[[nodiscard]] TEXTAUTOGENERATETEXT_EXPORT QStringList skillsList(const KSharedConfig::Ptr &config);

/*!
 * \brief agentConfigFileName
 * \return
 */
[[nodiscard]] TEXTAUTOGENERATETEXT_EXPORT QString agentConfigFileName();

/*!
 * \brief agentsList
 * \param config
 * \return
 */
[[nodiscard]] TEXTAUTOGENERATETEXT_EXPORT QStringList agentsList(const KSharedConfig::Ptr &config);
}
}
