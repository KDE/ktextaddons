/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QHash>
#include <QMap>
#include <QObject>
#include <QStringList>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolClientCapabilities>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolImplementation>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPlugin>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerCapabilities>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSettings>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTool>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
#include <memory>
#include <optional>
#include <vector>
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolCreateMessageRequestParams;
class McpProtocolCreateMessageResult;
class McpProtocolElicitResult;
class McpProtocolPrompt;
class McpProtocolResource;
class McpProtocolRoot;
class McpProtocolServer;
class McpProtocolServerPrompt;
class McpProtocolServerResource;
class McpProtocolServerTool;
class McpProtocolServerToolCall;
/*!
 * \class TextAutoGenerateTextMcpProtocolCore::McpProtocolServerProtocolManager
 * \brief The McpProtocolServerProtocolManager class implements MCP protocol on server side
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateTextMcpProtocolCore/McpProtocolServerProtocolManager
 *
 * Answers initialize, ping, tools/list, tools/call, prompts/list, prompts/get, resources/list, resources/read,
 * completion/complete and logging/setLevel (lists are paginated), handles notifications/cancelled.
 * Server only has to register its tools with addTool(), its prompts with addPrompt() and its resources with addResource().
 * Prompts, resources and completions capabilities are announced when at least one of them is registered before client initialization.
 * Log messages are sent to client with sendLogMessage().
 * Requests are sent to client with requestSampling(), requestElicitation() and requestRoots() when client announced
 * matching capability: answer is emitted with samplingResultReceived(), elicitationResultReceived(), rootsReceived()
 * or clientRequestFailed().
 * Reimplement handleCustomRequest() and capabilities() to support other methods (resource templates…),
 * and completeResourceTemplate() to complete arguments of resource templates.
 */
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolServerProtocolManager : public QObject
{
    Q_OBJECT
public:
    /*!
     * \brief McpProtocolServerProtocolManager
     * \param transportType
     * \param parent
     */
    explicit McpProtocolServerProtocolManager(TextAutoGenerateTextMcpProtocolCore::McpProtocolPlugin::TransportType transportType, QObject *parent = nullptr);
    /*!
     * \brief ~McpProtocolServerProtocolManager
     */
    ~McpProtocolServerProtocolManager() override;

    /*!
     * \brief setSettings
     * \param settings
     */
    void setSettings(const TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings &settings);

    /*!
     * \brief start
     */
    void start();
    /*!
     * \brief stop
     */
    void stop();
    /*!
     * \brief isRunning
     * \return
     */
    [[nodiscard]] bool isRunning() const;

    /*!
     * \brief setServerInfo
     * Name and version sent in initialize result. When they are not set,
     * QCoreApplication::applicationName() and applicationVersion() (or library version) are used.
     */
    void setServerInfo(const TextAutoGenerateTextMcpProtocolCore::McpProtocolImplementation &serverInfo);
    /*!
     * \brief setInstructions
     * \param instructions
     */
    void setInstructions(const QString &instructions);
    /*!
     * \brief setToolsPageSize
     * Number of items by page in tools/list, prompts/list and resources/list results.
     */
    void setToolsPageSize(int size);

    /*!
     * \brief addTool
     * Register \a tool (a tool with same name is replaced). Client is informed when server is running.
     */
    void addTool(std::unique_ptr<TextAutoGenerateTextMcpProtocolCore::McpProtocolServerTool> tool);
    /*!
     * \brief removeTool
     * \param name
     * \return true if tool was found
     */
    bool removeTool(const QString &name);
    /*!
     * \brief tools
     * \return definition of registered tools
     */
    [[nodiscard]] QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolTool> tools() const;

    /*!
     * \brief addPrompt
     * Register \a prompt (a prompt with same name is replaced). Client is informed when server is running.
     */
    void addPrompt(std::unique_ptr<TextAutoGenerateTextMcpProtocolCore::McpProtocolServerPrompt> prompt);
    /*!
     * \brief removePrompt
     * \param name
     * \return true if prompt was found
     */
    bool removePrompt(const QString &name);
    /*!
     * \brief prompts
     * \return definition of registered prompts
     */
    [[nodiscard]] QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolPrompt> prompts() const;

    /*!
     * \brief addResource
     * Register \a resource (a resource with same uri is replaced). Client is informed when server is running.
     */
    void addResource(std::unique_ptr<TextAutoGenerateTextMcpProtocolCore::McpProtocolServerResource> resource);
    /*!
     * \brief removeResource
     * \param uri
     * \return true if resource was found
     */
    bool removeResource(const QString &uri);
    /*!
     * \brief resources
     * \return definition of registered resources
     */
    [[nodiscard]] QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolResource> resources() const;

    /*!
     * \brief send
     * \param obj
     */
    void send(const QJsonObject &obj);
    /*!
     * \brief sendResult
     * \param id
     * \param result
     */
    void sendResult(const QJsonValue &id, const QJsonObject &result);
    /*!
     * \brief sendError
     * \param id
     * \param code
     * \param message
     */
    void sendError(const QJsonValue &id, int code, const QString &message);
    /*!
     * \brief sendLogMessage
     * Send a log message (notifications/message) with \a level, \a data and optional \a logger name.
     * Message is not sent when server is not running or when \a level is lower than loggingLevel().
     */
    void sendLogMessage(TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel level, const QJsonValue &data, const QString &logger = {});
    /*!
     * \brief loggingLevel
     * \return minimum level of log messages sent to client (set by client with logging/setLevel). Info by default.
     */
    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::LoggingLevel loggingLevel() const;

    /*!
     * \brief clientCapabilities
     * \return capabilities sent by client in initialize request (empty before initialization)
     */
    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolClientCapabilities clientCapabilities() const;
    /*!
     * \brief requestSampling
     * Ask client to generate a message with its LLM (sampling/createMessage). Answer is emitted with samplingResultReceived().
     * \return request id, or -1 when server is not running, client doesn't support sampling (or tools when \a params contains tools)
     * or \a params is invalid
     */
    qint64 requestSampling(const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequestParams &params);
    /*!
     * \brief requestElicitation
     * Ask user for information (elicitation/create) with a form or an url. Answer is emitted with elicitationResultReceived().
     * \return request id, or -1 when server is not running, client doesn't support this elicitation mode or \a params is invalid
     */
    qint64 requestElicitation(const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::ElicitRequestParams &params);
    /*!
     * \brief requestRoots
     * Ask client for its roots (roots/list). Answer is emitted with rootsReceived().
     * \return request id, or -1 when server is not running or client doesn't support roots
     */
    qint64 requestRoots();
    /*!
     * \brief cancelClientRequest
     * Cancel request \a requestId sent to client (notifications/cancelled). No answer is emitted for it anymore.
     */
    void cancelClientRequest(qint64 requestId, const QString &reason = {});

    /*!
     * JSON-RPC error codes
     */
    static constexpr int methodNotFoundCode = -32601;
    static constexpr int invalidParamsCode = -32602;
    static constexpr int internalErrorCode = -32603;
    /*!
     * MCP error code: resources/read with an unknown uri
     */
    static constexpr int resourceNotFoundCode = -32002;
    /*!
     * Maximum number of values in a completion/complete result
     */
    static constexpr int maxCompletionValues = 100;

Q_SIGNALS:
    /*!
     * \brief logMessage
     * \param str
     */
    void logMessage(const QString &str);
    /*!
     * \brief runningChanged
     * \param running
     */
    void runningChanged(bool running);
    /*!
     * \brief samplingResultReceived
     * Client answered sampling request \a requestId.
     */
    void samplingResultReceived(qint64 requestId, const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageResult &result);
    /*!
     * \brief elicitationResultReceived
     * Client answered elicitation request \a requestId (accepted, declined or cancelled by user).
     */
    void elicitationResultReceived(qint64 requestId, const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult &result);
    /*!
     * \brief rootsReceived
     * Client answered roots request \a requestId.
     */
    void rootsReceived(qint64 requestId, const QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolRoot> &roots);
    /*!
     * \brief clientRequestFailed
     * Client returned an error for request \a requestId (e.g. user rejected sampling), or client disconnected.
     */
    void clientRequestFailed(qint64 requestId, int code, const QString &message);
    /*!
     * \brief rootsListChanged
     * Client informs that its roots changed: call requestRoots() to get them.
     */
    void rootsListChanged();

protected:
    /*!
     * \brief capabilities
     * \return capabilities sent in initialize result. By default tools, and prompts and resources when some are registered.
     */
    [[nodiscard]] virtual TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities capabilities() const;
    /*!
     * \brief handleCustomRequest
     * Called for methods not handled by manager. Return false if \a method is not supported (method not found error is sent).
     */
    virtual bool handleCustomRequest(const QJsonValue &id, const QByteArray &method, const QJsonObject &params);
    /*!
     * \brief completeResourceTemplate
     * Return completion values for argument \a argumentName of resource template \a uri which starts with \a value.
     * \a arguments contains values of arguments already resolved by client.
     * Return nullopt when resource template is unknown (invalid params error is sent). By default no resource template is known.
     */
    [[nodiscard]] virtual std::optional<QStringList>
    completeResourceTemplate(const QString &uri, const QString &argumentName, const QString &value, const QMap<QString, QString> &arguments) const;

private:
    enum class ClientRequestType : uint8_t {
        Sampling,
        Elicitation,
        Roots,
    };
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void slotReceived(const QJsonObject &obj);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void handleClientResponse(const QJsonObject &obj);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void handleNotification(const QJsonObject &obj);
    [[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT qint64 sendClientRequest(ClientRequestType type, const QJsonObject &request);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void failAllClientRequests(const QString &message);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void slotError(const QString &str);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void slotStarted();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void slotFinished();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void handleRequest(const QJsonObject &obj);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void initialize(const QJsonValue &id, const QJsonObject &params);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void listTools(const QJsonValue &id, const QJsonObject &params);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void callTool(const QJsonValue &id, const QJsonObject &params);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void listPrompts(const QJsonValue &id, const QJsonObject &params);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void getPrompt(const QJsonValue &id, const QJsonObject &params);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void listResources(const QJsonValue &id, const QJsonObject &params);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void readResource(const QJsonValue &id, const QJsonObject &params);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void complete(const QJsonValue &id, const QJsonObject &params);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void setLoggingLevel(const QJsonValue &id, const QJsonObject &params);
    // Return first item of requested page, nullopt when cursor is invalid (error is sent)
    [[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT std::optional<qsizetype>
    pageStart(const QJsonValue &id, const QJsonObject &params, qsizetype count);
    [[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT std::optional<QString> nextCursor(qsizetype start, qsizetype count) const;
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void cancelRequest(const QJsonObject &obj);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void cancelAllCalls();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void cancelToolCalls(const QString &name);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void removeCall(const QString &key);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void sendToolListChanged();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void sendNotification(const QJsonObject &notification);
    [[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT McpProtocolServerTool *findTool(const QString &name) const;
    [[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT McpProtocolServerPrompt *findPrompt(const QString &name) const;
    [[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT McpProtocolServerResource *findResource(const QString &uri) const;

    std::vector<std::unique_ptr<McpProtocolServerTool>> mTools;
    std::vector<std::unique_ptr<McpProtocolServerPrompt>> mPrompts;
    std::vector<std::unique_ptr<McpProtocolServerResource>> mResources;
    // Key: request id type and value
    QHash<QString, McpProtocolServerToolCall *> mPendingCalls;
    // Requests sent to client, waiting for answer
    QHash<qint64, ClientRequestType> mPendingClientRequests;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolClientCapabilities mClientCapabilities;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolImplementation mServerInfo;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings mSettings;
    QString mInstructions;
    McpProtocolServer *const mServer;
    int mToolsPageSize = 50;
    qint64 mNextClientRequestId = 1;
    McpProtocolUtils::LoggingLevel mLoggingLevel = McpProtocolUtils::LoggingLevel::Info;
    bool mRunning = false;
};
}
