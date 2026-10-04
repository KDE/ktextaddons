/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QHash>
#include <QJsonObject>
#include <QObject>
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>
#include <chrono>
#include <functional>
#include <optional>

namespace TextAutoGenerateTextMcpProtocolCore
{
class McpServerManager;
class McpProtocolClientProtocolManager;
}

namespace TextAutoGenerateText
{
/*!
 * \class TextAutoGenerateText::TextAutoGenerateMcpToolsManager
 * \brief Connects to MCP servers and provides their tools to LLM.
 * Connection is created when a server is used (connectServer()), and closed
 * when server is removed, disabled or modified.
 */
class TEXTAUTOGENERATETEXT_EXPORT TextAutoGenerateMcpToolsManager : public QObject
{
    Q_OBJECT
public:
    enum class Status : uint8_t {
        Disconnected,
        Connecting,
        Connected,
        Error,
    };
    Q_ENUM(Status)

    struct TEXTAUTOGENERATETEXT_EXPORT McpTool {
        QByteArray serverIdentifier;
        // Name used by MCP server
        QString name;
        // Unique name sent to LLM ("server__tool")
        QByteArray exposedName;
        QString description;
        QJsonObject inputSchema;
        bool readOnly = false;
        [[nodiscard]] bool operator==(const McpTool &other) const = default;
    };

    explicit TextAutoGenerateMcpToolsManager(TextAutoGenerateTextMcpProtocolCore::McpServerManager *serverManager, QObject *parent = nullptr);
    ~TextAutoGenerateMcpToolsManager() override;

    /*!
     * Connect to server \a identifier if it's not done yet, its tools are loaded when connected.
     */
    void connectServer(const QByteArray &identifier);
    void disconnectServer(const QByteArray &identifier);

    [[nodiscard]] Status status(const QByteArray &identifier) const;
    [[nodiscard]] QString errorString(const QByteArray &identifier) const;

    [[nodiscard]] QList<McpTool> tools(const QByteArray &serverIdentifier) const;
    [[nodiscard]] std::optional<McpTool> tool(const QByteArray &exposedName) const;

    /*!
     * Tools of servers \a serverIdentifiers in LLM format ({"type":"function","function":{...}}).
     */
    [[nodiscard]] QList<QJsonObject> toolsMetaData(const QList<QByteArray> &serverIdentifiers) const;

    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolClientProtocolManager *client(const QByteArray &serverIdentifier) const;

    /*!
     * Connect to \a serverIdentifiers and call \a callback when their tools are loaded
     * (or when connection failed, or after \a timeout). \a callback is not called if \a context is deleted.
     */
    void prepareServers(const QList<QByteArray> &serverIdentifiers,
                        QObject *context,
                        const std::function<void()> &callback,
                        std::chrono::milliseconds timeout = std::chrono::seconds(30));
    [[nodiscard]] bool isReady(const QByteArray &serverIdentifier) const;

    /*!
     * Identifier used in list of selected tools for MCP server \a serverIdentifier ("mcp:<identifier>").
     */
    [[nodiscard]] static QByteArray toolIdentifier(const QByteArray &serverIdentifier);
    [[nodiscard]] static bool isMcpToolIdentifier(const QByteArray &toolIdentifier);
    [[nodiscard]] static QByteArray serverIdentifier(const QByteArray &toolIdentifier);
    /*!
     * MCP servers of list of selected tools \a tools
     */
    [[nodiscard]] static QList<QByteArray> serverIdentifiers(const QList<QByteArray> &tools);

    /*!
     * Convert \a name to a name accepted by LLM API: [a-zA-Z0-9_-]
     */
    [[nodiscard]] static QByteArray sanitizeName(const QString &name);

Q_SIGNALS:
    void statusChanged(const QByteArray &identifier);
    void toolsChanged(const QByteArray &identifier);

private:
    struct ServerState {
        TextAutoGenerateTextMcpProtocolCore::McpServer server;
        TextAutoGenerateTextMcpProtocolCore::McpProtocolClientProtocolManager *client = nullptr;
        Status status = Status::Disconnected;
        QString errorString;
        QList<McpTool> tools;
        qint64 listToolsRequestId = -1;
    };
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotServersChanged();
    TEXTAUTOGENERATETEXT_NO_EXPORT void setStatus(const QByteArray &identifier, Status status, const QString &errorString = {});
    TEXTAUTOGENERATETEXT_NO_EXPORT void listTools(const QByteArray &identifier);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotReceived(const QByteArray &identifier, const QJsonObject &obj, qint64 requestId);
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT QByteArray exposedName(const QByteArray &identifier, const QString &serverName, const QString &toolName) const;
    TextAutoGenerateTextMcpProtocolCore::McpServerManager *const mServerManager;
    QHash<QByteArray, ServerState> mServers;
};
}
