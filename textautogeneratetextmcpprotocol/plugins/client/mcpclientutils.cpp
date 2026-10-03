/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "mcpclientutils.h"
#include "autogeneratetext_mcpprotocolclientplugin_lib_debug.h"
#include <QNetworkRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolError>

using namespace Qt::Literals::StringLiterals;

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
