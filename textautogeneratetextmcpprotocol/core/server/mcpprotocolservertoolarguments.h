/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QJsonValue>
#include <QMap>
#include <QStringList>
#include <optional>

namespace TextAutoGenerateTextMcpProtocolCore
{
/*!
 * \namespace TextAutoGenerateTextMcpProtocolCore::McpProtocolServerToolArguments
 * \brief Readers of arguments received by McpProtocolServerTool::call()
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateTextMcpProtocolCore/McpProtocolServerToolArguments
 *
 * Language models often send numbers and booleans as strings ("60", "true"): they are accepted.
 */
namespace McpProtocolServerToolArguments
{
/*!
 * Returns true if \a value is neither undefined nor null.
 */
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT bool isProvided(const QJsonValue &value);
/*!
 * Returns integer of \a value (number without fractional part or string), std::nullopt otherwise.
 */
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT std::optional<qint64> integer(const QJsonValue &value);
/*!
 * Returns number of \a value (number or string), std::nullopt otherwise.
 */
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT std::optional<double> number(const QJsonValue &value);
/*!
 * Returns boolean of \a value (boolean, "true" or "false"), std::nullopt otherwise.
 */
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT std::optional<bool> boolean(const QJsonValue &value);
/*!
 * Appends the non-empty trimmed strings of array \a value to \a list.
 * An argument which is not provided is accepted, returns false if \a value is not an array of strings.
 */
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT bool readStringList(const QJsonValue &value, QStringList &list);
/*!
 * Sets \a result to the trimmed string of argument \a key when it's provided, an empty string is a valid value.
 * Returns false if argument is provided but is not a string.
 */
[[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT bool
readOptionalString(const QMap<QString, QJsonValue> &arguments, const QString &key, std::optional<QString> &result);
}
}
