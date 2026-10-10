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
#include <QMap>
#include <QObject>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolInitializeResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolUtils>
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>
#include <chrono>
class QJsonObject;
class QTimer;
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolClient;
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

Q_SIGNALS:
    void started();
    void initialized();
    void received(const QJsonObject &obj, McpProtocolClientProtocolManager::MethodType type);
    void error(const QString &str);
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
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void slotReceived(const QJsonObject &obj);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void slotFinished();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void initializeResponseReceived(const QJsonObject &obj);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void answerServerRequest(const QJsonObject &obj);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void serverNotificationReceived(const QJsonObject &obj);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT qint64 sendRequest(const QJsonObject &request, qint64 identifier, MethodType type);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT qint64 sendRequest(const QJsonObject &request, qint64 identifier, MethodType type, PendingRequest pending);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void sendCancelledNotification(qint64 identifier, const QString &reason);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void checkTimeouts();
    [[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT bool serverSupports(MethodType type) const;
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
    bool mElicitationSupported = false;
};
}
