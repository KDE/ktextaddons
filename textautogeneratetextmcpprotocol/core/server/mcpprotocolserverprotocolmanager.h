/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#pragma once

#include "textautogeneratetextmcpprotocolcore_export.h"
#include <QHash>
#include <QObject>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolImplementation>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolPlugin>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolServerCapabilities>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolSettings>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolTool>
#include <memory>
#include <vector>
class QJsonObject;
namespace TextAutoGenerateTextMcpProtocolCore
{
class McpProtocolServer;
class McpProtocolServerTool;
class McpProtocolServerToolCall;
/*!
 * \class TextAutoGenerateTextMcpProtocolCore::McpProtocolServerProtocolManager
 * \brief The McpProtocolServerProtocolManager class implements MCP protocol on server side
 * \author Laurent Montel <montel@kde.org>
 * \inmodule TextAutoGenerateText
 * \inheaderfile TextAutoGenerateTextMcpProtocolCore/McpProtocolServerProtocolManager
 *
 * Answers initialize, ping, tools/list (paginated) and tools/call, handles notifications/cancelled.
 * Server only has to register its tools with addTool().
 * Reimplement handleCustomRequest() and capabilities() to support other methods (prompts, resources…).
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
     * Name and version sent in initialize result.
     */
    void setServerInfo(const TextAutoGenerateTextMcpProtocolCore::McpProtocolImplementation &serverInfo);
    /*!
     * \brief setInstructions
     * \param instructions
     */
    void setInstructions(const QString &instructions);
    /*!
     * \brief setToolsPageSize
     * Number of tools by page in tools/list result.
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
     * JSON-RPC error codes
     */
    static constexpr int methodNotFoundCode = -32601;
    static constexpr int invalidParamsCode = -32602;

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

protected:
    /*!
     * \brief capabilities
     * \return capabilities sent in initialize result. By default only tools.
     */
    [[nodiscard]] virtual TextAutoGenerateTextMcpProtocolCore::McpProtocolServerCapabilities capabilities() const;
    /*!
     * \brief handleCustomRequest
     * Called for methods not handled by manager. Return false if \a method is not supported (method not found error is sent).
     */
    virtual bool handleCustomRequest(const QJsonValue &id, const QByteArray &method, const QJsonObject &params);

private:
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void slotReceived(const QJsonObject &obj);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void slotError(const QString &str);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void slotStarted();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void slotFinished();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void handleRequest(const QJsonObject &obj);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void initialize(const QJsonValue &id, const QJsonObject &params);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void listTools(const QJsonValue &id, const QJsonObject &params);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void callTool(const QJsonValue &id, const QJsonObject &params);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void cancelRequest(const QJsonObject &obj);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void cancelAllCalls();
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void removeCall(const QString &key);
    TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT void sendToolListChanged();
    [[nodiscard]] TEXTAUTOGENERATETEXTMCPPROTOCOLCORE_NO_EXPORT McpProtocolServerTool *findTool(const QString &name) const;

    std::vector<std::unique_ptr<McpProtocolServerTool>> mTools;
    // Key: request id as string
    QHash<QString, McpProtocolServerToolCall *> mPendingCalls;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolImplementation mServerInfo;
    TextAutoGenerateTextMcpProtocolCore::McpProtocolSettings mSettings;
    QString mInstructions;
    McpProtocolServer *const mServer;
    int mToolsPageSize = 50;
    bool mRunning = false;
};
}
