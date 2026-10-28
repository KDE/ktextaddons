/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <KSharedConfig>
#include <QByteArray>
#include <QString>
#include <QUrl>
#include <functional>
class QObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolSettings;
/*!
 * \namespace TextAutoGenerateTextMcpProtocolCore::McpProtocolServerUtils
 * \brief Helpers to manage the bearer token required by the MCP server
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateTextMcpProtocolCore/McpProtocolServerUtils
 */
namespace McpProtocolServerUtils
{
/*!
 * Generate a new random token (32 bytes encoded in base64url)
 */
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QByteArray generateAuthToken();
/*!
 * Identifier used to store the server token in the system wallet.
 * Each config file \a configName has its own token, so several servers can coexist
 */
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QByteArray authTokenIdentifier(const QString &configName = {});
/*!
 * Store the server token in the system wallet
 */
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT void writeAuthToken(const QByteArray &token, const QString &configName = {});
/*!
 * Read the server token from the system wallet. \a callback is called with an empty token on error
 */
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT void
readAuthToken(QObject *context, std::function<void(const QByteArray &)> callback, const QString &configName = {});
/*!
 * Remove the server token from the system wallet
 */
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT void removeAuthToken(const QString &configName = {});
/*!
 * Default url where server listens (streamable http transport)
 */
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT QUrl defaultServerUrl();
/*!
 * Load server settings. Token is read from the system wallet, so \a callback can be called asynchronously
 */
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT void loadSettings(QObject *context, std::function<void(const McpProtocolSettings &)> callback);
/*!
 * Save server settings. Token is stored in the system wallet
 */
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT void saveSettings(const McpProtocolSettings &settings);

/*!
 * \brief loadSettings
 * \param config
 * \param context
 * \param callback
 */
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT void
loadSettings(const KSharedConfig::Ptr &config, QObject *context, std::function<void(const McpProtocolSettings &)> callback);
/*!
 * \brief saveSettings
 * \param config
 * \param settings
 */
TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT void saveSettings(const KSharedConfig::Ptr &config, const McpProtocolSettings &settings);
}
}
