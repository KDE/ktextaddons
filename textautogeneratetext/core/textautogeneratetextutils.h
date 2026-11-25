/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextcore_export.h"
#include <KSharedConfig>
#include <QString>
namespace TextAutoGenerateText
{
/*!
 * \namespace TextAutoGenerateText::TextAutoGenerateTextUtils
 * \inmodule TextAutoGenerateTextCore
 * \inheaderfile TextAutoGenerateText/TextAutoGenerateTextUtils
 */
namespace TextAutoGenerateTextUtils
{
/*!
 */
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_EXPORT QString instanceConfigFileName();
/*!
 */
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_EXPORT QStringList instancesList(const KSharedConfig::Ptr &config);
/*!
 */
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_EXPORT QByteArray generateUUid();

/*!
 * \brief promptConfigFileName
 * \return
 */
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_EXPORT QString promptConfigFileName();

/*!
 * \brief promptsList
 * \param config
 * \return
 */
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_EXPORT QStringList promptsList(const KSharedConfig::Ptr &config);

/*!
 * \brief skillConfigFileName
 * \return
 */
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_EXPORT QString skillConfigFileName();

/*!
 * \brief skillsList
 * \param config
 * \return
 */
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_EXPORT QStringList skillsList(const KSharedConfig::Ptr &config);

/*!
 * \brief agentConfigFileName
 * \return
 */
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_EXPORT QString agentConfigFileName();

/*!
 * \brief agentsList
 * \param config
 * \return
 */
[[nodiscard]] TEXTAUTOGENERATETEXTCORE_EXPORT QStringList agentsList(const KSharedConfig::Ptr &config);
}
}
