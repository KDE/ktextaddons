/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QUrl>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerProtocolManager>
/*
 * Minimal MCP server used to test client: declares tools, protocol is handled by McpProtocolServerProtocolManager.
 * Answers too prompts and resource templates requests.
 * Tools list is paginated (2 tools by page) to test pagination.
 */
class McpTestServer : public TextAutoGenerateTextMcpProtocolCore::McpProtocolServerProtocolManager
{
    Q_OBJECT
public:
    explicit McpTestServer(QObject *parent = nullptr);
    ~McpTestServer() override;

    void start(const QUrl &url);

    // Add or remove "reverse" tool and send notifications/tools/list_changed
    void toggleExtraTool();
    // Send a ping request to client (in event stream)
    void pingClient();

protected:
    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities capabilities() const override;
    bool handleCustomRequest(const QJsonValue &id, const QByteArray &method, const QJsonObject &params) override;

private:
    void getPrompt(const QJsonValue &id, const QJsonObject &params);

    int mServerRequestId = 0;
    bool mExtraTool = false;
};
