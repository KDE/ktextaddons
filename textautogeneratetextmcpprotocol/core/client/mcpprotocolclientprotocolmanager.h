/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QDeadlineTimer>
#include <QHash>
#include <QJsonArray>
#include <QList>
#include <QMap>
#include <QObject>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolInitializeResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolRoot>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>
#include <chrono>
class QJsonObject;
class QTimer;
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolClient;
class McpProtocolCreateMessageRequest;
class McpProtocolCreateMessageResult;
class McpProtocolElicitResult;
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
    };
    Q_ENUM(MethodType)
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
     * Server requested user input: answer it with respondToElicitation().
     * Without any receiver connected, the request is declined automatically.
     */
    void elicitationRequested(const McpProtocolUtils::RequestId &id, const McpProtocolElicitRequest &request);

    /*!
     * Server requested a LLM generation: answer it with respondToSampling() or rejectSampling().
     * Without any receiver connected, the request is rejected automatically.
     */
    void samplingRequested(const McpProtocolUtils::RequestId &id, const McpProtocolCreateMessageRequest &request);

private:
    struct PendingRequest {
        MethodType type = MethodType::Unknown;
        QDeadlineTimer deadline;
        // Id returned to caller: list requests use several requests (one by page)
        qint64 originalId = 0;
        // Pagination
        QString cursor;
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
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT qint64 sendRequest(const QJsonObject &request, qint64 identifier, MethodType type);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT qint64 sendRequest(const QJsonObject &request, qint64 identifier, MethodType type, PendingRequest pending);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void sendCancelledNotification(qint64 identifier, const QString &reason);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void checkTimeouts();
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
    bool mRootsSupported = false;
    bool mSamplingSupported = false;
};
}
