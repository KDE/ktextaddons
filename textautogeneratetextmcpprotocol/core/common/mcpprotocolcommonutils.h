/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once
#include "textautogeneratetextmcpprotocolcore_export.h"
#include <KSharedConfig>
#include <QStringList>
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolMeta;
namespace McpProtocolCommonUtils
{
/*!
 */
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QString serverConfigFileName();
/*!
 */
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QByteArray generateUUid();
/*!
 * \brief mcpServerList
 * \param config
 * \return
 */
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QStringList mcpServerList(const KSharedConfig::Ptr &config);
/*!
 * \brief generateAuthToken
 * \return
 */
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QByteArray generateAuthToken();

/*!
 * \brief addToolMeta
 * \param meta
 * \param groupName
 * \param groupTitle
 */
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT void
addToolMeta(TextAutoGenerateTextMcpProtocolCore::McpProtocolMeta &meta, const QString &groupName, const QString &groupTitle);

/*!
 * \brief McpProtocolCommonUtils::metaGroupName
 * \return
 */
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QString metaGroupName();
/*!
 * \brief McpProtocolCommonUtils::metaGroupTitle
 * \return
 */
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QString metaGroupTitle();
}
}
