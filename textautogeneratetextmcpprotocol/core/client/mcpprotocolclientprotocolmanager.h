/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QHash>
#include <QObject>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolInitializeResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolClient;
class TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_EXPORT McpProtocolClientProtocolManager : public QObject
{
    Q_OBJECT
public:
    enum class MethodType : uint8_t {
        Unknown = 0,
        Ping,
        ListTools,
        ListPrompts,
        ResourceTemplates,
        Initialize,
        ServerRequest,
        ServerNotification,
    };
    Q_ENUM(MethodType)
    explicit McpProtocolClientProtocolManager(const TextAutoGenerateTextMcpProtocolCore::McpServer &server, QObject *parent = nullptr);
    ~McpProtocolClientProtocolManager() override;

    void initializeClient();

    void executeAction(MethodType type);

    [[nodiscard]] QString clientName() const;
    void setClientName(const QString &newClientName);

    [[nodiscard]] bool isInitialized() const;
    [[nodiscard]] TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeResult initializeResult() const;

Q_SIGNALS:
    void started();
    void initialized();
    void received(const QJsonObject &obj, McpProtocolClientProtocolManager::MethodType type);
    void error(const QString &str);
    void finished();

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void ping();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void listTools();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void listPrompts();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void resourceTemplates();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void initialize();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void sendInitializedNotification();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void slotReceived(const QJsonObject &obj);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void slotFinished();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void initializeResponseReceived(const QJsonObject &obj);
    [[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT qint64 requestId();
    [[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT McpProtocolClientProtocolManager::MethodType checkMethodType(const QJsonObject &obj);

    QString mClientName;

    qint64 mRequestIdentifier = 0;
    bool mClientStarted = false;
    bool mInitialized = false;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolInitializeResult mInitializeResult;
    TextAutoGenerateTextMcpProtocolCore::McpServer mServer;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolClient *mClient = nullptr;
    QHash<qint64, McpProtocolClientProtocolManager::MethodType> mMapIdentifier;
};
}
