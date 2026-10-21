/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QUrl>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerProtocolManager>
/*
 * Minimal MCP server used to test client: declares tools, protocol is handled by McpProtocolServerProtocolManager.
 * Declares too a prompt and a resource, answers resource templates requests.
 * Tools list is paginated (2 tools by page) to test pagination.
 * Tools ask_name, summarize and list_roots send elicitation, sampling and roots requests to client.
 */
class McpTestServer : public TextAutoGenerateTextMcpProtocolCore::McpProtocolServerProtocolManager
{
    Q_OBJECT
public:
    explicit McpTestServer(QObject *parent = nullptr);
    ~McpTestServer() override;

    void start(const QUrl &url, const QString &token);

    // Add or remove "reverse" tool and send notifications/tools/list_changed
    void toggleExtraTool();
    // Send a ping request to client (in event stream)
    void pingClient();

protected:
    bool handleCustomRequest(const QJsonValue &id, const QByteArray &method, const QJsonObject &params) override;

private:
    int mServerRequestId = 0;
    bool mExtraTool = false;
};
