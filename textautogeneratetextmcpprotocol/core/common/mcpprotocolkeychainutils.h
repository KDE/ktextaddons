/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#pragma once

#include <QByteArray>
#include <functional>
class QObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
namespace McpProtocolKeychainUtils
{
void writeAuthToken(const QByteArray &serverIdentifier, const QByteArray &token);
// callback is called with an empty token on error
void readAuthToken(const QByteArray &serverIdentifier, QObject *context, std::function<void(const QByteArray &)> callback);
void removeAuthToken(const QByteArray &serverIdentifier);
}
}
