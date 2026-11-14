/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientutils.h"
#include "autogeneratetext_mcpprotocolclientplugin_lib_debug.h"
#include <KLocalizedString>
#include <QNetworkReply>
#include <QNetworkRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolError>

using namespace Qt::Literals::StringLiterals;

void McpClientUtils::addBearer(QNetworkRequest &request, const QByteArray &token)
{
    if (token.isEmpty()) {
        return;
    }
    if (request.hasRawHeader("Authorization"_ba)) {
        qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Authorization header replaced by auth token";
    }
    request.setRawHeader("Authorization"_ba, "Bearer "_ba + token);
}

void McpClientUtils::addHeaders(QNetworkRequest &request, const QStringList &headers)
{
    for (const QString &header : headers) {
        const qsizetype index = header.indexOf(u':');
        if (index <= 0) {
            qCWarning(AUTOGENERATETEXT_MCPPROTOCOLCLIENT_PLUGIN_LIB_LOG) << "Invalid header, expected \"Name: Value\"";
            continue;
        }
        request.setRawHeader(header.left(index).trimmed().toUtf8(), header.mid(index + 1).trimmed().toUtf8());
    }
}

namespace
{
[[nodiscard]] bool isSpace(char c)
{
    return c == ' ' || c == '\t';
}
}

McpClientUtils::BearerChallenge McpClientUtils::parseBearerChallenge(const QByteArray &header)
{
    // Header contains challenges: scheme followed by auth-params ("name=value" or "name=\"quoted value\"")
    BearerChallenge challenge;
    const qsizetype size = header.size();
    qsizetype pos = 0;
    bool inBearer = false;
    while (true) {
        while (pos < size && (isSpace(header.at(pos)) || header.at(pos) == ',')) {
            ++pos;
        }
        if (pos >= size) {
            break;
        }
        const qsizetype tokenStart = pos;
        while (pos < size && header.at(pos) != '=' && header.at(pos) != ',' && !isSpace(header.at(pos))) {
            ++pos;
        }
        const QByteArray token = header.mid(tokenStart, pos - tokenStart);
        qsizetype next = pos;
        while (next < size && isSpace(header.at(next))) {
            ++next;
        }
        if (next < size && header.at(next) == '=') {
            // auth-param
            pos = next + 1;
            while (pos < size && isSpace(header.at(pos))) {
                ++pos;
            }
            QByteArray value;
            if (pos < size && header.at(pos) == '"') {
                ++pos;
                while (pos < size && header.at(pos) != '"') {
                    if (header.at(pos) == '\\' && pos + 1 < size) {
                        ++pos;
                    }
                    value += header.at(pos);
                    ++pos;
                }
                // Closing quote
                ++pos;
            } else {
                const qsizetype valueStart = pos;
                while (pos < size && header.at(pos) != ',' && !isSpace(header.at(pos))) {
                    ++pos;
                }
                value = header.mid(valueStart, pos - valueStart);
            }
            if (!inBearer) {
                continue;
            }
            const QByteArray name = token.toLower();
            if (name == "error") {
                challenge.error = value;
            } else if (name == "error_description") {
                challenge.errorDescription = QString::fromUtf8(value);
            } else if (name == "scope") {
                challenge.scope = QString::fromUtf8(value);
            } else if (name == "resource_metadata") {
                challenge.resourceMetadata = QUrl(QString::fromUtf8(value));
            }
        } else {
            // New challenge
            if (inBearer) {
                break;
            }
            inBearer = token.compare("bearer", Qt::CaseInsensitive) == 0;
            challenge.isValid = inBearer;
            pos = next;
        }
    }
    return challenge;
}

QString McpClientUtils::authorizationErrorMessage(const QNetworkReply *reply)
{
    const int statusCode = reply->attribute(QNetworkRequest::HttpStatusCodeAttribute).toInt();
    if (statusCode != 401 && statusCode != 403) {
        return {};
    }
    const BearerChallenge challenge = parseBearerChallenge(reply->rawHeader("WWW-Authenticate"_ba));
    QString message;
    if (statusCode == 401) {
        if (reply->request().hasRawHeader("Authorization"_ba)) {
            message = i18n("Authentication failed: the server rejected the access token.");
        } else if (challenge.resourceMetadata.isValid()) {
            message = i18n("Authentication required. The server uses OAuth authorization, which is not supported: set an access token in the server settings.");
        } else {
            message = i18n("Authentication required: set an access token in the server settings.");
        }
    } else if (challenge.error == "insufficient_scope") {
        message = challenge.scope.isEmpty() ? i18n("Access denied: the access token does not grant the required permissions.")
                                            : i18n("Access denied: the access token does not grant the required permissions (%1).", challenge.scope);
    } else {
        message = i18n("Access denied by the server.");
    }
    if (!challenge.errorDescription.isEmpty()) {
        message += u' ' + i18n("Server message: %1", challenge.errorDescription);
    }
    return message;
}

QJsonObject McpClientUtils::createConnectionErrorResponse(const QJsonValue &requestId, const QString &errorMessage)
{
    TextAutoGenerateTextMcpProtocolCore::McpProtocolError mcpError;
    // JSON-RPC implementation-defined error (-32000 to -32099)
    mcpError.setCode(-32000);
    mcpError.setMessage(errorMessage);
    // Use original id value, response must have same id as request
    return QJsonObject{
        {"jsonrpc"_L1, u"2.0"_s},
        {"id"_L1, requestId},
        {"error"_L1, TextAutoGenerateTextMcpProtocolCore::McpProtocolError::toJson(mcpError)},
    };
}
