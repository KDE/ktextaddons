/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QDateTime>
#include <QDeadlineTimer>
#include <QElapsedTimer>
#include <QHash>
#include <QJsonArray>
#include <QJsonObject>
#include <QList>
#include <QMap>
#include <QObject>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolInitializeResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolRoot>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>
#include <chrono>
#include <optional>
class QTimer;
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolClient;
class McpProtocolCompleteRequestParams;
class McpProtocolCreateMessageRequest;
class McpProtocolCreateMessageResult;
class McpProtocolElicitResult;
class McpProtocolLoggingMessageNotificationParams;
class McpProtocolProgressNotificationParams;
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolClientProtocolManager : public QObject
{
    Q_OBJECT
public:
    enum class MethodType : uint8_t {
        Unknown = 0,
        Ping,
        ListTools,
        ListPrompts,
        ListResources,
        ResourceTemplates,
        Initialize,
        ServerRequest,
        ServerNotification,
        CallTool,
        GetPrompt,
        ReadResource,
        SubscribeResource,
        UnsubscribeResource,
        Complete,
        SetLoggingLevel,
    };
    Q_ENUM(MethodType)

    enum class MessageDirection : uint8_t {
        Sent = 0,
        Received,
    };
    Q_ENUM(MessageDirection)

    /*!
     * Request sent to server or message received from server, emitted with messageLogged().
     */
    struct MessageInfo {
        QJsonObject message;
        QDateTime dateTime;
        // Numeric JSON-RPC id, -1 for notifications or string id
        qint64 identifier = -1;
        MethodType type = MethodType::Unknown;
        MessageDirection direction = MessageDirection::Sent;
        // Time between request and its response, -1 otherwise
        qint64 elapsedMs = -1;
    };

    explicit McpProtocolClientProtocolManager(const TextAutoGenerateTextMcpProtocolCore::McpServer &server, QObject *parent = nullptr);
    ~McpProtocolClientProtocolManager() override;

    void initializeClient();
    void stopClient();

    /*!
     * Send request \a type. Return request id, -1 if request was not sent.
     */
    qint64 executeAction(MethodType type);
    /*!
     * Cancel request \a requestId: server is informed and we stop waiting for response.
     */
    void cancelRequest(qint64 requestId, const QString &reason = {});

    /*!
     * Call tool \a name with \a arguments. Server must support tools.
     * Response is emitted with received() and MethodType::CallTool, its "result" can be
     * read with McpProtocolCallToolResult::fromJson(). Return request id, -1 if request was not sent.
     */
    [[nodiscard]] qint64 callTool(const QString &name, const QJsonObject &arguments = {});

    /*!
     * Get prompt \a name with \a arguments. Server must support prompts.
     * Response is emitted with received() and MethodType::GetPrompt, its "result" can be
     * read with McpProtocolGetPromptResult::fromJson(). Return request id, -1 if request was not sent.
     */
    [[nodiscard]] qint64 getPrompt(const QString &name, const QMap<QString, QString> &arguments = {});

    /*!
     * Time to wait for a response. When it expires, request is cancelled and
     * an error response (code -32001) is emitted with received().
     */
    [[nodiscard]] std::chrono::milliseconds requestTimeout() const;
    void setRequestTimeout(std::chrono::milliseconds timeout);

    /*!
     * \brief clientName
     * \return
     */
    [[nodiscard]] QString clientName() const;
    /*!
     * \brief setClientName
     * \param newClientName
     */
    void setClientName(const QString &newClientName);

    /*!
     * \brief isInitialized
     * \return
     */
    [[nodiscard]] bool isInitialized() const;
    /*!
     * \brief initializeResult
     * \return
     */
    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeResult initializeResult() const;

    /*!
     * Read resource \a uri. Server must support resources.
     * Response is emitted with received() and MethodType::ReadResource, its "result" can be
     * read with McpProtocolReadResourceResult::fromJson(). Return request id, -1 if request was not sent.
     */
    [[nodiscard]] qint64 readResource(const QString &uri);

    /*!
     * Subscribe to updates of resource \a uri: resourceUpdated() is then emitted when it changes.
     * Server must support resources subscription. Response is emitted with received() and
     * MethodType::SubscribeResource. Return request id, -1 if request was not sent.
     */
    [[nodiscard]] qint64 subscribeResource(const QString &uri);
    /*!
     * Stop receiving updates of resource \a uri. Response is emitted with received() and
     * MethodType::UnsubscribeResource. Return request id, -1 if request was not sent.
     */
    [[nodiscard]] qint64 unsubscribeResource(const QString &uri);

    /*!
     * Ask completion values for an argument of a prompt or of a resource template (\a params).
     * Server must support completions. Response is emitted with received() and MethodType::Complete,
     * its "result" can be read with McpProtocolCompleteResult::fromJson(). Return request id, -1 if request was not sent.
     */
    [[nodiscard]] qint64 complete(const McpProtocolCompleteRequestParams &params);

    /*!
     * Ask server to send log messages with \a level or higher (emitted with loggingMessageReceived()).
     * Server must support logging. Response is emitted with received() and MethodType::SetLoggingLevel.
     * Return request id, -1 if request was not sent.
     */
    [[nodiscard]] qint64 setLoggingLevel(McpProtocolUtils::LoggingLevel level);

    /*!
     * Return true if "elicitation" capability (form mode) is announced to server.
     */
    [[nodiscard]] bool elicitationSupported() const;
    /*!
     * Announce "elicitation" capability (form mode) to server when \a supported is true.
     * Only enable it when something answers elicitation/create requests (e.g. a dialog),
     * it must be called before initializeClient(). Default is false.
     */
    void setElicitationSupported(bool supported);

    /*!
     * Return true if "elicitation" capability url mode is announced to server.
     */
    [[nodiscard]] bool urlElicitationSupported() const;
    /*!
     * Announce "elicitation" capability url mode to server when \a supported is true.
     * Server can then ask user to open an URL (authorization…): elicitationRequested() is emitted with
     * McpProtocolElicitRequestURLParams. URL must be opened only when user accepted it.
     * It must be called before initializeClient(). Default is false.
     */
    void setUrlElicitationSupported(bool supported);

    /*!
     * Send the answer \a result to the elicitation request \a id received with elicitationRequested().
     */
    void respondToElicitation(const McpProtocolUtils::RequestId &id, const McpProtocolElicitResult &result);

    /*!
     * Return true if "roots" capability is announced to server.
     */
    [[nodiscard]] bool rootsSupported() const;
    /*!
     * Announce "roots" capability to server when \a supported is true: server can then
     * ask for roots() with roots/list. It must be called before initializeClient(). Default is false.
     */
    void setRootsSupported(bool supported);

    /*!
     * Directories (file:// uri) that server is allowed to access.
     */
    [[nodiscard]] QList<McpProtocolRoot> roots() const;
    /*!
     * Set \a roots. When client is initialized, server is informed that list changed.
     */
    void setRoots(const QList<McpProtocolRoot> &roots);

    /*!
     * Return true if "sampling" capability is announced to server.
     */
    [[nodiscard]] bool samplingSupported() const;
    /*!
     * Announce "sampling" capability to server when \a supported is true.
     * Only enable it when something answers sampling/createMessage requests (e.g. LLM after user confirmation),
     * it must be called before initializeClient(). Default is false.
     */
    void setSamplingSupported(bool supported);

    /*!
     * Send the generated message \a result to the sampling request \a id received with samplingRequested().
     */
    void respondToSampling(const McpProtocolUtils::RequestId &id, const McpProtocolCreateMessageResult &result);
    /*!
     * Reject the sampling request \a id received with samplingRequested() (e.g. user refused it).
     */
    void rejectSampling(const McpProtocolUtils::RequestId &id, const QString &message = {});

    /*!
     * \brief serverSupports
     * \param type
     * \return
     */
    [[nodiscard]] bool serverSupports(MethodType type) const;

Q_SIGNALS:
    /*!
     * \brief started
     */
    void started();
    /*!
     * \brief initialized
     */
    void initialized();
    /*!
     * \brief received
     * \param obj
     * \param type
     */
    void received(const QJsonObject &obj, McpProtocolClientProtocolManager::MethodType type);
    /*!
     * \brief error
     * \param str
     */
    void error(const QString &str);
    /*!
     * \brief finished
     */
    void finished();
    /*!
     * Server informed that list of tools changed: call executeAction(MethodType::ListTools) to update it.
     */
    void toolsListChanged();
    /*!
     * Server informed that list of prompts changed.
     */
    void promptsListChanged();
    /*!
     * Server informed that list of resources changed.
     */
    void resourcesListChanged();
    /*!
     * Subscribed resource \a uri changed: call readResource() to get new content.
     */
    void resourceUpdated(const QString &uri);

    /*!
     * Server sent a log message (notifications/message).
     */
    void loggingMessageReceived(const TextAutoGenerateTextMcpProtocolCore::McpProtocolLoggingMessageNotificationParams &params);

    /*!
     * Server informed about progress of request \a requestId (id returned by callTool()).
     * Request timeout is restarted on each progress notification.
     */
    void progressReceived(qint64 requestId, const TextAutoGenerateTextMcpProtocolCore::McpProtocolProgressNotificationParams &params);

    /*!
     * Server requested user input: answer it with respondToElicitation().
     * Without any receiver connected, the request is declined automatically.
     */
    void elicitationRequested(const McpProtocolUtils::RequestId &id, const McpProtocolElicitRequest &request);

    /*!
     * Server requested a LLM generation: answer it with respondToSampling() or rejectSampling().
     * Without any receiver connected, the request is rejected automatically.
     */
    void samplingRequested(const McpProtocolUtils::RequestId &id, const McpProtocolCreateMessageRequest &request);

    /*!
     * Server cancelled elicitation or sampling request \a id: close dialog, answer is not sent anymore.
     */
    void userRequestCancelled(const McpProtocolUtils::RequestId &id);

    /*!
     * Server informs that the url mode elicitation \a elicitationId is completed (user finished interaction in browser).
     */
    void elicitationCompleted(const QString &elicitationId);

    /*!
     * Emitted for each request sent to server and for each message received from server
     * (raw message, before pagination is merged). Useful to inspect traffic.
     */
    void messageLogged(const TextAutoGenerateTextMcpProtocolCore::McpProtocolClientProtocolManager::MessageInfo &info);

private:
    struct PendingRequest {
        MethodType type = MethodType::Unknown;
        QDeadlineTimer deadline;
        // Time since request was sent
        QElapsedTimer elapsed;
        // Id returned to caller: list requests use several requests (one by page)
        qint64 originalId = 0;
        // Pagination
        std::optional<QString> cursor;
        QJsonArray items;
        int pageCount = 0;
    };
    [[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT qint64 ping();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT qint64 listRequest(MethodType type);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT qint64 listRequest(MethodType type, PendingRequest pending);
    [[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT bool processPaginatedResponse(QJsonObject &obj, PendingRequest &pending);
    [[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT static QString listKey(MethodType type);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void initialize();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void sendInitializedNotification();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void sendResult(const McpProtocolUtils::RequestId &id, const QJsonObject &result);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void sendError(const McpProtocolUtils::RequestId &id, int code, const QString &message);
    [[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT bool takePendingUserRequest(const McpProtocolUtils::RequestId &id);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void slotReceived(const QJsonObject &obj);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void slotFinished();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void initializeResponseReceived(const QJsonObject &obj);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void answerServerRequest(const QJsonObject &obj);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void serverNotificationReceived(const QJsonObject &obj);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void progressNotificationReceived(const QJsonObject &obj);
    [[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT qint64 resourceSubscriptionRequest(const QString &uri, MethodType type);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT qint64 sendRequest(const QJsonObject &request, qint64 identifier, MethodType type);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT qint64 sendRequest(const QJsonObject &request, qint64 identifier, MethodType type, PendingRequest pending);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void sendCancelledNotification(qint64 identifier, const QString &reason);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void checkTimeouts();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void logReceivedMessage(const QJsonObject &message);
    [[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT qint64 requestId();

    QString mClientName;

    qint64 mRequestIdentifier = 0;
    bool mClientStarted = false;
    bool mInitialized = false;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeResult mInitializeResult;
    TextAutoGenerateTextMcpProtocolCore::McpServer mServer;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolClient *mClient = nullptr;
    QHash<qint64, PendingRequest> mPendingRequests;
    std::chrono::milliseconds mRequestTimeout = std::chrono::seconds(60);
    QTimer *const mTimeoutTimer;
    // Elicitation/sampling requests waiting for user answer: requests don't time out meanwhile
    QList<McpProtocolUtils::RequestId> mPendingUserRequests;
    QList<McpProtocolRoot> mRoots;
    bool mElicitationSupported = false;
    bool mUrlElicitationSupported = false;
    bool mRootsSupported = false;
    bool mSamplingSupported = false;
};
}
Q_DECLARE_METATYPE(TextAutoGenerateTextMcpProtocolCore::McpProtocolClientProtocolManager::MessageInfo)
