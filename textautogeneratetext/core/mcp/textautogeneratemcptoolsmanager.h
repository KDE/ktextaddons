/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetext_private_export.h"
#include <QHash>
#include <QJsonObject>
#include <QObject>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCreateMessageRequest>
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
class McpProtocolElicitRequestURLParams;
class McpProtocolRoot;
}

namespace TextAutoGenerateText
{
class TextAutoGenerateTextPlugin;
/*!
 * \class TextAutoGenerateText::TextAutoGenerateMcpToolsManager
 * \brief Connects to MCP servers and provides their tools to LLM.
 * Connection is created when a server is used (connectServer()), and closed
 * when server is removed, disabled or modified.
 */
class TEXTAUTOGENERATETEXT_TESTS_EXPORT TextAutoGenerateMcpToolsManager : public QObject
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

    // Risk of a tool, deduced from MCP annotations (missing hints mean worst case)
    enum class ToolRisk : uint8_t {
        ReadOnly,
        Modify,
        Destructive,
    };
    Q_ENUM(ToolRisk)

    struct TEXTAUTOGENERATETEXT_TESTS_EXPORT McpTool {
        QByteArray serverIdentifier;
        // Name used by MCP server
        QString name;
        QString displayName;
        // Unique name sent to LLM ("server__tool")
        QByteArray exposedName;
        QString description;
        QJsonObject inputSchema;
        ToolRisk risk = ToolRisk::Destructive;
        // Group of tool defined in _meta ("org.kde/group", "org.kde/groupTitle"), empty when tool has no group
        QString groupName;
        QString groupTitle;
        [[nodiscard]] bool operator==(const McpTool &other) const = default;
    };

    enum class ToolConfirmation : uint8_t {
        Deny,
        Allow,
        // Allow and don't ask anymore for tools of this server
        AlwaysAllowServer,
    };
    Q_ENUM(ToolConfirmation)

    struct TEXTAUTOGENERATETEXT_TESTS_EXPORT ToolConfirmationInfo {
        McpTool tool;
        QString serverName;
        QJsonObject arguments;
    };
    /*!
     * Asks user to confirm tool call, \a answer must be called with user choice.
     */
    using ConfirmationHandler = std::function<void(const ToolConfirmationInfo &info, const std::function<void(ToolConfirmation)> &answer)>;

    struct TEXTAUTOGENERATETEXT_TESTS_EXPORT ElicitationInfo {
        QString serverName;
        TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequest request;
    };
    /*!
     * Asks user to answer an elicitation request of a MCP server, \a answer must be called with user answer.
     */
    using ElicitationHandler = std::function<void(const ElicitationInfo &info,
                                                  const std::function<void(const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult &)> &answer)>;

    struct TEXTAUTOGENERATETEXT_TESTS_EXPORT SamplingInfo {
        QString serverName;
        TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequest request;
    };
    /*!
     * Asks user to confirm that sampling request of a MCP server can be sent to LLM, \a answer must be called with user choice.
     */
    using SamplingHandler = std::function<void(const SamplingInfo &info, const std::function<void(bool accepted)> &answer)>;
    /*!
     * Returns LLM plugin used to answer sampling requests (can be nullptr).
     */
    using PluginProvider = std::function<TextAutoGenerateTextPlugin *()>;

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
    /*!
     * Returns tool named \a exposedName. LLM can drop server prefix of exposed name (it uses tool names found in descriptions
     * or results of other tools), so a tool whose sanitized name is \a exposedName is returned when it's unique.
     */
    [[nodiscard]] std::optional<McpTool> tool(const QByteArray &exposedName) const;

    /*!
     * Replace in \a text the names of tools of server \a serverIdentifier by their exposed names, see replaceToolNames().
     */
    [[nodiscard]] QString replaceToolNames(const QByteArray &serverIdentifier, const QString &text) const;

    /*!
     * Tools of servers \a serverIdentifiers in LLM format ({"type":"function","function":{...}}).
     */
    [[nodiscard]] QList<QJsonObject> toolsMetaData(const QList<QByteArray> &serverIdentifiers) const;
    /*!
     * Tools selected by \a toolIdentifiers ("mcp:<server>" for all tools of server, "mcp:<server>/<tool>" for one tool).
     */
    [[nodiscard]] QList<McpTool> selectedTools(const QList<QByteArray> &toolIdentifiers) const;
    /*!
     * Tool \a tool in LLM format ({"type":"function","function":{...}}).
     */
    [[nodiscard]] static QJsonObject toolMetaData(const McpTool &tool);

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
    /*!
     * Identifier used in list of selected tools for tool \a toolName of MCP server \a serverIdentifier ("mcp:<identifier>/<tool>").
     */
    [[nodiscard]] static QByteArray toolIdentifier(const QByteArray &serverIdentifier, const QString &toolName);
    [[nodiscard]] static bool isMcpToolIdentifier(const QByteArray &toolIdentifier);
    [[nodiscard]] static QByteArray serverIdentifier(const QByteArray &toolIdentifier);
    /*!
     * Name of tool of \a toolIdentifier, empty when all tools of server are selected.
     */
    [[nodiscard]] static QString toolName(const QByteArray &toolIdentifier);
    /*!
     * Tool \a tool is selected by \a toolIdentifiers.
     */
    [[nodiscard]] static bool isToolSelected(const McpTool &tool, const QList<QByteArray> &toolIdentifiers);
    /*!
     * MCP servers of list of selected tools \a tools (without duplicate)
     */
    [[nodiscard]] static QList<QByteArray> serverIdentifiers(const QList<QByteArray> &tools);

    /*!
     * Convert \a name to a name accepted by LLM API: [a-zA-Z0-9_-]
     */
    [[nodiscard]] static QByteArray sanitizeName(const QString &name);

    /*!
     * Replace in \a text the names of \a tools by their exposed names: servers refer to their tools by name
     * in descriptions and results, LLM must see the exposed name to call them.
     * Only whole words are replaced, and only names which can't be a common word (they contain '_', '-', a digit
     * or an uppercase letter after first character).
     */
    [[nodiscard]] static QString replaceToolNames(const QString &text, const QList<McpTool> &tools);

    /*!
     * Convert local directories \a paths to MCP roots (file:// uri, name of directory).
     */
    [[nodiscard]] static QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolRoot> convertToRoots(const QStringList &paths);

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
     * Handler used to confirm sampling requests of MCP servers before sending them to LLM returned by plugin provider.
     * Without handler sampling is not announced to servers. It must be defined before connecting to servers.
     */
    void setSamplingHandler(const SamplingHandler &handler);
    void setPluginProvider(const PluginProvider &provider);
    /*!
     * Tool needs a confirmation: handler is defined, tool is not read only and server is not always allowed.
     */
    [[nodiscard]] bool needConfirmation(const McpTool &tool) const;
    /*!
     * Ask confirmation if needed and call \a callback with result (true: tool can be called).
     * \a callback is not called if \a context is deleted.
     */
    void confirmToolCall(const McpTool &tool, const QJsonObject &arguments, QObject *context, const std::function<void(bool)> &callback);
    /*!
     * Server \a serverIdentifier needs that user opens \a elicitations URLs (e.g. authorization) before a request can succeed.
     * They are shown with elicitation handler, an URL is opened only when user accepts it.
     * Return false when there is no elicitation handler.
     */
    bool showUrlElicitations(const QByteArray &serverIdentifier,
                             const QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams> &elicitations);

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
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotSamplingRequested(const QString &serverName,
                                                              TextAutoGenerateTextMcpProtocolCore::McpProtocolClientProtocolManager *client,
                                                              const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::RequestId &id,
                                                              const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequest &request);
    TEXTAUTOGENERATETEXT_NO_EXPORT void slotReceived(const QByteArray &identifier, const QJsonObject &obj, qint64 requestId);
    [[nodiscard]] TEXTAUTOGENERATETEXT_NO_EXPORT QByteArray exposedName(const QByteArray &identifier, const QString &serverName, const QString &toolName) const;
    TextAutoGenerateTextMcpProtocolCore::McpServerManager *const mServerManager;
    QHash<QByteArray, ServerState> mServers;
    ConfirmationHandler mConfirmationHandler;
    ElicitationHandler mElicitationHandler;
    SamplingHandler mSamplingHandler;
    PluginProvider mPluginProvider;
};
}
