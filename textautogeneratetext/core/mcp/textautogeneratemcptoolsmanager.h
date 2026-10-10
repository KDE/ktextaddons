/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_export.h"
#include <QHash>
#include <QJsonObject>
#include <QObject>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequest>
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>
#include <chrono>
#include <functional>
#include <optional>

namespace TextAutoGenerateTextMcpProtocolCore
{
class McpServerManager;
class McpProtocolClientProtocolManager;
class McpProtocolElicitResult;
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

    enum class ToolConfirmation : uint8_t {
        Deny,
        Allow,
        // Allow and don't ask anymore for tools of this server
        AlwaysAllowServer,
    };
    Q_ENUM(ToolConfirmation)

    struct TEXTAUTOGENERATETEXT_EXPORT ToolConfirmationInfo {
        McpTool tool;
        QString serverName;
        QJsonObject arguments;
    };
    /*!
     * Asks user to confirm tool call, \a answer must be called with user choice.
     */
    using ConfirmationHandler = std::function<void(const ToolConfirmationInfo &info, const std::function<void(ToolConfirmation)> &answer)>;

    struct TEXTAUTOGENERATETEXT_EXPORT ElicitationInfo {
        QString serverName;
        TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequest request;
    };
    /*!
     * Asks user to answer an elicitation request of a MCP server, \a answer must be called with user answer.
     */
    using ElicitationHandler = std::function<void(const ElicitationInfo &info,
                                                  const std::function<void(const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult &)> &answer)>;

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

    /*!
     * Handler used to ask user before calling a tool. Without handler tools are called without confirmation.
     */
    void setConfirmationHandler(const ConfirmationHandler &handler);
    /*!
     * Handler used to answer elicitation requests of MCP servers. Without handler elicitation is not announced to servers.
     * It must be defined before connecting to servers.
     */
    void setElicitationHandler(const ElicitationHandler &handler);
    /*!
     * Tool needs a confirmation: handler is defined, tool is not read only and server is not always allowed.
     */
    [[nodiscard]] bool needConfirmation(const McpTool &tool) const;
    /*!
     * Ask confirmation if needed and call \a callback with result (true: tool can be called).
     * \a callback is not called if \a context is deleted.
     */
    void confirmToolCall(const McpTool &tool, const QJsonObject &arguments, QObject *context, const std::function<void(bool)> &callback);

    [[nodiscard]] bool isServerAlwaysAllowed(const QByteArray &serverIdentifier) const;
    void setServerAlwaysAllowed(const QByteArray &serverIdentifier, bool allowed);

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
    ConfirmationHandler mConfirmationHandler;
    ElicitationHandler mElicitationHandler;
};
}
