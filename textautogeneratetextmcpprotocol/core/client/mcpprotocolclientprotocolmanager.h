/*
 * SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>
 *
 * SPDX-License-Identifier: LGPL-2.0-or-later
 */

#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QHash>
#include <QObject>
#include <TextAutoGenerateTextMcpProtocolCore/McpServer>
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolClient;
}
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
    };
    Q_ENUM(MethodType)
    explicit McpProtocolClientProtocolManager(const TextAutoGenerateTextMcpProtocolCore::McpServer &server, QObject *parent = nullptr);
    ~McpProtocolClientProtocolManager() override;

    void initializeClient(bool started);

    [[nodiscard]] int requestId();

    void executeAction(MethodType type);

    [[nodiscard]] QString clientName() const;
    void setClientName(const QString &newClientName);

Q_SIGNALS:
    void started();
    void received(const QJsonObject &obj, McpProtocolClientProtocolManager::MethodType type);
    void error(const QString &str);

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void ping();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void listTools();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void listPrompts();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void resouceTemplates();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void initialize();
    [[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT McpProtocolClientProtocolManager::MethodType checkMethodType(const QJsonObject &obj) const;

    QString mClientName;

    int mRequestIdentifier = 0;
    TextAutoGenerateTextMcpProtocolCore::McpServer mServer;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolClient *mClient = nullptr;
    QHash<int, McpProtocolClientProtocolManager::MethodType> mMapIdentifier;
};
