/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "mcpprotocolclientplugin_export.h"
#include <QJsonObject>
#include <QJsonValue>
#include <QStringList>
#include <QUrl>
class QNetworkReply;
class QNetworkRequest;
namespace McpClientUtils
{
/*!
 * Parameters of the "Bearer" challenge of a WWW-Authenticate header (RFC 6750, RFC 9728)
 */
struct BearerChallenge {
    QByteArray error;
    QString errorDescription;
    QString scope;
    // Protected resource metadata, used by OAuth discovery
    QUrl resourceMetadata;
    bool isValid = false;
};

/*!
 * Parse the "Bearer" challenge of WWW-Authenticate header \a header
 */
[[nodiscard]] MCPPROTOCOLCLIENTPLUGIN_EXPORT BearerChallenge parseBearerChallenge(const QByteArray &header);
/*!
 * Return a user readable message when \a reply was rejected because of authorization (401/403), an empty string otherwise.
 */
[[nodiscard]] MCPPROTOCOLCLIENTPLUGIN_EXPORT QString authorizationErrorMessage(const QNetworkReply *reply);
/*!
 * Add user headers ("Name: Value") to \a request
 */
MCPPROTOCOLCLIENTPLUGIN_EXPORT void addHeaders(QNetworkRequest &request, const QStringList &headers);
/*!
 * Create a JSON-RPC error response for request \a requestId, used when server can't answer anymore.
 */
[[nodiscard]] MCPPROTOCOLCLIENTPLUGIN_EXPORT QJsonObject createConnectionErrorResponse(const QJsonValue &requestId, const QString &errorMessage);

/*!
 * \brief addBearer
 * \param request
 * \param token
 */
MCPPROTOCOLCLIENTPLUGIN_EXPORT void addBearer(QNetworkRequest &request, const QByteArray &token);
}
