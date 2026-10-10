/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemcptoolsmanager.h"
#include "textautogeneratetextcore_debug.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QPointer>
#include <QTimer>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolClientProtocolManager>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolJSONRPCErrorResponse>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListToolsResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerManager>
#include <TextAutoGenerateTextMcpProtocolCore/McpServerModel>
#include <memory>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
using TextAutoGenerateTextMcpProtocolCore::McpProtocolClientProtocolManager;

namespace
{
// Maximum length of a function name (OpenAI API)
constexpr qsizetype maxNameLength = 64;
}

TextAutoGenerateMcpToolsManager::TextAutoGenerateMcpToolsManager(TextAutoGenerateTextMcpProtocolCore::McpServerManager *serverManager, QObject *parent)
    : QObject{parent}
    , mServerManager(serverManager)
{
    // Server removed, disabled or modified: close its connection
    auto model = mServerManager->mcpServerModel();
    connect(model, &QAbstractItemModel::dataChanged, this, &TextAutoGenerateMcpToolsManager::slotServersChanged);
    connect(model, &QAbstractItemModel::rowsRemoved, this, &TextAutoGenerateMcpToolsManager::slotServersChanged);
    connect(model, &QAbstractItemModel::modelReset, this, &TextAutoGenerateMcpToolsManager::slotServersChanged);
}

TextAutoGenerateMcpToolsManager::~TextAutoGenerateMcpToolsManager()
{
    for (auto &state : mServers) {
        if (state.client) {
            // Don't emit signals while we are destroyed
            state.client->disconnect(this);
            state.client->stopClient();
        }
    }
}

void TextAutoGenerateMcpToolsManager::slotServersChanged()
{
    const QList<QByteArray> identifiers = mServers.keys();
    for (const QByteArray &identifier : identifiers) {
        const TextAutoGenerateTextMcpProtocolCore::McpServer server = mServerManager->mcpServerModel()->mcpServer(identifier);
        if (server != mServers.value(identifier).server || !server.enabled()) {
            qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << "MCP server changed, disconnect it:" << identifier;
            disconnectServer(identifier);
        }
    }
}

void TextAutoGenerateMcpToolsManager::connectServer(const QByteArray &identifier)
{
    if (const auto it = mServers.constFind(identifier); it != mServers.cend() && (it->status == Status::Connecting || it->status == Status::Connected)) {
        return;
    }
    const TextAutoGenerateTextMcpProtocolCore::McpServer server = mServerManager->mcpServerModel()->mcpServer(identifier);
    ServerState &state = mServers[identifier];
    state.server = server;
    if (!server.isValid() || !server.enabled()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Invalid or disabled MCP server:" << identifier;
        setStatus(identifier, Status::Error, i18n("Server is invalid or disabled."));
        return;
    }
    auto client = new McpProtocolClientProtocolManager(server, this);
    state.client = client;
    connect(client, &McpProtocolClientProtocolManager::initialized, this, [this, identifier]() {
        // Request tools before changing status: server is ready when its tools are loaded
        listTools(identifier);
        setStatus(identifier, Status::Connected);
    });
    connect(client, &McpProtocolClientProtocolManager::toolsListChanged, this, [this, identifier]() {
        listTools(identifier);
    });
    connect(client,
            &McpProtocolClientProtocolManager::received,
            this,
            [this, identifier](const QJsonObject &obj, McpProtocolClientProtocolManager::MethodType type) {
                if (type == McpProtocolClientProtocolManager::MethodType::ListTools) {
                    slotReceived(identifier, obj, obj.value("id"_L1).toInteger(-1));
                }
            });
    connect(client, &McpProtocolClientProtocolManager::error, this, [this, identifier](const QString &errorString) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "MCP server error:" << identifier << errorString;
        if (mServers.value(identifier).status == Status::Connecting) {
            setStatus(identifier, Status::Error, errorString);
        }
    });
    connect(client, &McpProtocolClientProtocolManager::finished, this, [this, identifier]() {
        auto it = mServers.find(identifier);
        if (it == mServers.end()) {
            return;
        }
        // Server stopped: tools can't be used anymore
        it->tools.clear();
        it->listToolsRequestId = -1;
        Q_EMIT toolsChanged(identifier);
        if (it->status != Status::Error) {
            setStatus(identifier, Status::Disconnected);
        }
    });
    connect(client,
            &McpProtocolClientProtocolManager::elicitationRequested,
            this,
            [client](const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::RequestId &id,
                     const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequest &request) {
                Q_UNUSED(request) // TODO: show form dialog
                TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult result;
                result.setAction(TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult::Action::Decline);
                client->respondToElicitation(id, result);
            });
    setStatus(identifier, Status::Connecting);
    client->initializeClient();
}

void TextAutoGenerateMcpToolsManager::disconnectServer(const QByteArray &identifier)
{
    const auto it = mServers.find(identifier);
    if (it == mServers.end()) {
        return;
    }
    const bool hadTools = !it->tools.isEmpty();
    if (auto client = it->client) {
        client->disconnect(this);
        client->stopClient();
        // Let client send end of session (DELETE request) before deleting it.
        // It's deleted with this manager if it's deleted before.
        QTimer::singleShot(std::chrono::seconds(5), client, &QObject::deleteLater);
    }
    mServers.erase(it);
    if (hadTools) {
        Q_EMIT toolsChanged(identifier);
    }
    Q_EMIT statusChanged(identifier);
}

void TextAutoGenerateMcpToolsManager::setStatus(const QByteArray &identifier, Status status, const QString &errorString)
{
    ServerState &state = mServers[identifier];
    state.status = status;
    state.errorString = errorString;
    Q_EMIT statusChanged(identifier);
}

void TextAutoGenerateMcpToolsManager::listTools(const QByteArray &identifier)
{
    ServerState &state = mServers[identifier];
    if (!state.client) {
        return;
    }
    // -1 when server doesn't support tools
    state.listToolsRequestId = state.client->executeAction(McpProtocolClientProtocolManager::MethodType::ListTools);
}

void TextAutoGenerateMcpToolsManager::slotReceived(const QByteArray &identifier, const QJsonObject &obj, qint64 requestId)
{
    const auto it = mServers.find(identifier);
    if (it == mServers.end() || it->listToolsRequestId != requestId) {
        return;
    }
    it->listToolsRequestId = -1;
    if (!obj.contains("result"_L1)) {
        const auto response = TextAutoGenerateTextMcpProtocolCore::McpProtocolJSONRPCErrorResponse::fromJson(obj);
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Impossible to list tools of" << identifier << response.error().message();
        return;
    }
    const auto result = TextAutoGenerateTextMcpProtocolCore::McpProtocolListToolsResult::fromJson(obj.value("result"_L1).toObject());
    // Remove current tools first: their names must not be used to create new names
    it->tools.clear();
    QList<McpTool> tools;
    const auto mcpTools = result.tools();
    for (const auto &mcpTool : mcpTools) {
        McpTool tool;
        tool.serverIdentifier = identifier;
        tool.name = mcpTool.name();
        tool.exposedName = exposedName(identifier, it->server.name(), mcpTool.name());
        tool.description = mcpTool.description().value_or(QString());
        tool.inputSchema = TextAutoGenerateTextMcpProtocolCore::McpProtocolTool::InputSchema::toJson(mcpTool.inputSchema());
        if (const auto annotations = mcpTool.annotations(); annotations.has_value()) {
            tool.readOnly = annotations->readOnlyHint().value_or(false);
        }
        tools.append(std::move(tool));
        // Next tools of this server must not use same name
        it->tools = tools;
    }
    it->tools = std::move(tools);
    qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << "MCP server" << identifier << "has" << it->tools.count() << "tools";
    Q_EMIT toolsChanged(identifier);
}

QByteArray TextAutoGenerateMcpToolsManager::sanitizeName(const QString &name)
{
    QByteArray result;
    result.reserve(name.size());
    for (const QChar c : name) {
        if ((c >= u'a' && c <= u'z') || (c >= u'A' && c <= u'Z') || (c >= u'0' && c <= u'9') || c == u'_' || c == u'-') {
            result.append(c.toLatin1());
        } else {
            result.append('_');
        }
    }
    return result;
}

QByteArray TextAutoGenerateMcpToolsManager::exposedName(const QByteArray &identifier, const QString &serverName, const QString &toolName) const
{
    auto isUsed = [this](const QByteArray &name) {
        for (const auto &state : mServers) {
            for (const auto &tool : state.tools) {
                if (tool.exposedName == name) {
                    return true;
                }
            }
        }
        return false;
    };
    // Prefix with server name: two servers can provide tools with same name
    const QByteArray suffix = "__" + sanitizeName(toolName);
    QByteArray name = QByteArray(sanitizeName(serverName).left(maxNameLength / 3) + suffix).left(maxNameLength);
    if (isUsed(name)) {
        // Same server name: use server identifier
        const QByteArray prefix = sanitizeName(serverName).left(8) + '_' + sanitizeName(QString::fromLatin1(identifier)).left(8);
        name = QByteArray(prefix + suffix).left(maxNameLength);
    }
    int count = 1;
    const QByteArray baseName = name.left(maxNameLength - 4);
    while (isUsed(name)) {
        name = baseName + '_' + QByteArray::number(count++);
    }
    return name;
}

TextAutoGenerateMcpToolsManager::Status TextAutoGenerateMcpToolsManager::status(const QByteArray &identifier) const
{
    return mServers.value(identifier).status;
}

QString TextAutoGenerateMcpToolsManager::errorString(const QByteArray &identifier) const
{
    return mServers.value(identifier).errorString;
}

QList<TextAutoGenerateMcpToolsManager::McpTool> TextAutoGenerateMcpToolsManager::tools(const QByteArray &serverIdentifier) const
{
    return mServers.value(serverIdentifier).tools;
}

std::optional<TextAutoGenerateMcpToolsManager::McpTool> TextAutoGenerateMcpToolsManager::tool(const QByteArray &exposedName) const
{
    for (const auto &state : mServers) {
        for (const auto &tool : state.tools) {
            if (tool.exposedName == exposedName) {
                return tool;
            }
        }
    }
    return std::nullopt;
}

QList<QJsonObject> TextAutoGenerateMcpToolsManager::toolsMetaData(const QList<QByteArray> &serverIdentifiers) const
{
    QList<QJsonObject> list;
    for (const QByteArray &identifier : serverIdentifiers) {
        const auto serverTools = tools(identifier);
        for (const auto &tool : serverTools) {
            QJsonObject parameters = tool.inputSchema;
            // Some API require "properties" for an object
            if (!parameters.contains("properties"_L1)) {
                parameters.insert("properties"_L1, QJsonObject());
            }
            const QJsonObject functionObj{
                {"name"_L1, QString::fromLatin1(tool.exposedName)},
                {"description"_L1, tool.description},
                {"parameters"_L1, parameters},
            };
            list.append(QJsonObject{{"type"_L1, u"function"_s}, {"function"_L1, functionObj}});
        }
    }
    return list;
}

bool TextAutoGenerateMcpToolsManager::isReady(const QByteArray &serverIdentifier) const
{
    const auto it = mServers.constFind(serverIdentifier);
    if (it == mServers.cend()) {
        return false;
    }
    // Tools are loaded, or connection failed
    return it->status != Status::Connecting && it->listToolsRequestId == -1;
}

void TextAutoGenerateMcpToolsManager::prepareServers(const QList<QByteArray> &serverIdentifiers,
                                                     QObject *context,
                                                     const std::function<void()> &callback,
                                                     std::chrono::milliseconds timeout)
{
    for (const QByteArray &identifier : serverIdentifiers) {
        connectServer(identifier);
    }
    auto serversReady = [this, serverIdentifiers]() {
        return std::all_of(serverIdentifiers.cbegin(), serverIdentifiers.cend(), [this](const QByteArray &identifier) {
            return isReady(identifier);
        });
    };
    if (serversReady()) {
        callback();
        return;
    }
    // Deleted when callback is called, or with context
    auto waiter = new QObject(this);
    connect(context, &QObject::destroyed, waiter, &QObject::deleteLater);
    auto done = std::make_shared<bool>(false);
    auto finish = [this, waiter, callback, done]() {
        if (*done) {
            return;
        }
        *done = true;
        // Disconnect first: callback can change servers state
        disconnect(this, nullptr, waiter, nullptr);
        waiter->deleteLater();
        callback();
    };
    auto check = [serversReady, finish]() {
        if (serversReady()) {
            finish();
        }
    };
    connect(this, &TextAutoGenerateMcpToolsManager::statusChanged, waiter, check);
    connect(this, &TextAutoGenerateMcpToolsManager::toolsChanged, waiter, check);
    QTimer::singleShot(timeout, waiter, [finish]() {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Timeout when connecting to MCP servers";
        finish();
    });
}

QByteArray TextAutoGenerateMcpToolsManager::toolIdentifier(const QByteArray &serverIdentifier)
{
    return "mcp:" + serverIdentifier;
}

bool TextAutoGenerateMcpToolsManager::isMcpToolIdentifier(const QByteArray &toolIdentifier)
{
    return toolIdentifier.startsWith("mcp:");
}

QByteArray TextAutoGenerateMcpToolsManager::serverIdentifier(const QByteArray &toolIdentifier)
{
    return isMcpToolIdentifier(toolIdentifier) ? toolIdentifier.mid(4) : QByteArray();
}

QList<QByteArray> TextAutoGenerateMcpToolsManager::serverIdentifiers(const QList<QByteArray> &tools)
{
    QList<QByteArray> identifiers;
    for (const QByteArray &tool : tools) {
        if (isMcpToolIdentifier(tool)) {
            identifiers.append(serverIdentifier(tool));
        }
    }
    return identifiers;
}

void TextAutoGenerateMcpToolsManager::setConfirmationHandler(const ConfirmationHandler &handler)
{
    mConfirmationHandler = handler;
}

bool TextAutoGenerateMcpToolsManager::needConfirmation(const McpTool &tool) const
{
    return mConfirmationHandler && !tool.readOnly && !isServerAlwaysAllowed(tool.serverIdentifier);
}

void TextAutoGenerateMcpToolsManager::confirmToolCall(const McpTool &tool,
                                                      const QJsonObject &arguments,
                                                      QObject *context,
                                                      const std::function<void(bool)> &callback)
{
    if (!needConfirmation(tool)) {
        callback(true);
        return;
    }
    const ToolConfirmationInfo info{
        .tool = tool,
        .serverName = mServerManager->mcpServerModel()->mcpServer(tool.serverIdentifier).name(),
        .arguments = arguments,
    };
    const QPointer<QObject> guard(context);
    mConfirmationHandler(info, [this, guard, callback, serverIdentifier = tool.serverIdentifier](ToolConfirmation confirmation) {
        if (confirmation == ToolConfirmation::AlwaysAllowServer) {
            setServerAlwaysAllowed(serverIdentifier, true);
        }
        if (guard) {
            callback(confirmation != ToolConfirmation::Deny);
        }
    });
}

bool TextAutoGenerateMcpToolsManager::isServerAlwaysAllowed(const QByteArray &serverIdentifier) const
{
    const KConfigGroup group(KSharedConfig::openConfig(mServerManager->serverConfigFileName()), u"ToolConfirmation"_s);
    return group.readEntry("AlwaysAllowedServers", QStringList()).contains(QString::fromLatin1(serverIdentifier));
}

void TextAutoGenerateMcpToolsManager::setServerAlwaysAllowed(const QByteArray &serverIdentifier, bool allowed)
{
    KConfigGroup group(KSharedConfig::openConfig(mServerManager->serverConfigFileName()), u"ToolConfirmation"_s);
    QStringList servers = group.readEntry("AlwaysAllowedServers", QStringList());
    const QString identifier = QString::fromLatin1(serverIdentifier);
    servers.removeAll(identifier);
    if (allowed) {
        servers.append(identifier);
    }
    group.writeEntry("AlwaysAllowedServers", servers);
    group.sync();
}

McpProtocolClientProtocolManager *TextAutoGenerateMcpToolsManager::client(const QByteArray &serverIdentifier) const
{
    return mServers.value(serverIdentifier).client;
}

#include "moc_textautogeneratemcptoolsmanager.cpp"
