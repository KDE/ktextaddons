/*
   SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

   SPDX-License-Identifier: LGPL-2.0-or-later
*/
#pragma once

#include <QJsonObject>
#include <QObject>
#include <QSet>
#include <QUrl>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTool>
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolServer;
}
/*
 * Minimal MCP server used to test client: answers initialize, ping, tools, prompts and resource templates requests.
 * Tools list is paginated (2 tools by page) to test pagination.
 */
class McpTestServer : public QObject
{
    Q_OBJECT
public:
    explicit McpTestServer(QObject *parent = nullptr);
    ~McpTestServer() override;

    void start(const QUrl &url);
    void stop();
    [[nodiscard]] bool isRunning() const;

    // Add or remove "reverse" tool and send notifications/tools/list_changed
    void toggleExtraTool();
    // Send a ping request to client (in event stream)
    void pingClient();

Q_SIGNALS:
    void logMessage(const QString &str);
    void runningChanged(bool running);

private:
    void slotReceived(const QJsonObject &obj);
    void handleRequest(const QJsonObject &obj);
    void send(const QJsonObject &obj);
    void sendResult(const QJsonValue &id, const QJsonObject &result);
    void sendError(const QJsonValue &id, int code, const QString &message);
    void listTools(const QJsonValue &id, const QJsonObject &params);
    void callTool(const QJsonValue &id, const QJsonObject &params);
    void getPrompt(const QJsonValue &id, const QJsonObject &params);
    [[nodiscard]] QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolTool> tools() const;
    [[nodiscard]] static QString idToString(const QJsonValue &id);
    [[nodiscard]] static QJsonObject textResult(const QString &text, bool isError = false);

    TextAutoGenerateTextMcpProtocolCore::McpProtocolServer *const mServer;
    // Requests of "slow" tool not answered yet (can be cancelled by client)
    QSet<QString> mSlowRequests;
    int mServerRequestId = 0;
    bool mExtraTool = false;
    bool mRunning = false;
};
