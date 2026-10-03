/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "mcpprotocolclientplugin_export.h"
#include <QStringList>
class QNetworkRequest;
namespace McpClientUtils
{
/*!
 * Add user headers ("Name: Value") to \a request
 */
MCPPROTOCOLCLIENTPLUGIN_EXPORT void addHeaders(QNetworkRequest &request, const QStringList &headers);
}
