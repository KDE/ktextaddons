/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemcptoolsmanager.h"
#include "core/mcp/textautogeneratemcpsamplingjob.h"
#include "core/mcp/textautogeneratemcptoolsutils.h"
#include "textautogeneratetextcore_debug.h"
#include <KConfigGroup>
#include <KLocalizedString>
#include <KSharedConfig>
#include <QDir>
#include <QPointer>
#include <QRegularExpression>
#include <QTimer>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolClientProtocolManager>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCommonUtils>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCreateMessageResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitRequestURLParams>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolElicitResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolJSONRPCErrorResponse>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolListToolsResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolRoot>
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

TextAutoGenerateMcpToolsManager::ToolRisk toolRisk(const TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations &annotations)
{
    if (annotations.readOnlyHint().value_or(false)) {
        return TextAutoGenerateMcpToolsManager::ToolRisk::ReadOnly;
    }
    if (!annotations.destructiveHint().value_or(true)) {
        return TextAutoGenerateMcpToolsManager::ToolRisk::Modify;
    }
    return TextAutoGenerateMcpToolsManager::ToolRisk::Destructive;
}
}

bool TextAutoGenerateMcpToolsManager::McpTool::operator==(const McpTool &other) const
{
    return serverIdentifier == other.serverIdentifier && name == other.name && displayName == other.displayName && exposedName == other.exposedName
        && description == other.description && inputSchema == other.inputSchema && risk == other.risk && groupName == other.groupName
        && groupTitle == other.groupTitle;
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
    for (const auto &state : mServers) {
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
        ServerState &state = mServers[identifier];
        if (server == state.server) {
            continue;
        }
        if (!server.enabled() || !TextAutoGenerateMcpToolsUtils::sameConnectionSettings(server, state.server)) {
            qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << "MCP server changed, disconnect it:" << identifier;
            disconnectServer(identifier);
        } else {
            // Only allowed tools changed: connection can be kept
            state.server = server;
            Q_EMIT toolsChanged(identifier);
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
        const auto it = mServers.find(identifier);
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
    // Announce roots only when they are defined: some servers (e.g. filesystem) replace
    // their own allowed directories by client roots
    if (const QStringList roots = server.settings().roots(); !roots.isEmpty()) {
        client->setRootsSupported(true);
        client->setRoots(convertToRoots(roots));
    }
    if (mElicitationHandler) {
        client->setElicitationSupported(true);
        // Handler shows URL to user, it's opened only when user accepts it
        client->setUrlElicitationSupported(true);
        connect(client,
                &McpProtocolClientProtocolManager::elicitationRequested,
                this,
                [this, serverName = server.name(), client = QPointer(client)](const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::RequestId &id,
                                                                              const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequest &request) {
                    const ElicitationInfo info{
                        .serverName = serverName,
                        .request = request,
                    };
                    mElicitationHandler(info, [client, id](const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult &result) {
                        // Client can be deleted while user answers
                        if (client) {
                            client->respondToElicitation(id, result);
                        }
                    });
                });
    }
    if (mSamplingHandler) {
        client->setSamplingSupported(true);
        connect(client,
                &McpProtocolClientProtocolManager::samplingRequested,
                this,
                [this, serverName = server.name(), client](const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::RequestId &id,
                                                           const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequest &request) {
                    slotSamplingRequested(serverName, client, id, request);
                });
    }
    setStatus(identifier, Status::Connecting);
    client->initializeClient();
}

void TextAutoGenerateMcpToolsManager::slotSamplingRequested(const QString &serverName,
                                                            McpProtocolClientProtocolManager *client,
                                                            const TextAutoGenerateTextMcpProtocolCore::McpProtocolUtils::RequestId &id,
                                                            const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageRequest &request)
{
    const SamplingInfo info{
        .serverName = serverName,
        .request = request,
    };
    // Client can be deleted while user answers or while LLM generates message
    mSamplingHandler(info, [this, client = QPointer(client), id, request](bool accepted) {
        if (!client) {
            return;
        }
        if (!accepted) {
            client->rejectSampling(id);
            return;
        }
        auto job = new TextAutoGenerateMcpSamplingJob(mPluginProvider ? mPluginProvider() : nullptr, client);
        job->setRequest(request);
        connect(job,
                &TextAutoGenerateMcpSamplingJob::finished,
                client,
                [client, id](const TextAutoGenerateTextMcpProtocolCore::McpProtocolCreateMessageResult &result) {
                    client->respondToSampling(id, result);
                });
        connect(job, &TextAutoGenerateMcpSamplingJob::failed, client, [client, id](const QString &errorString) {
            client->rejectSampling(id, errorString);
        });
        job->start();
    });
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
        const auto annotations = mcpTool.annotations().value_or(TextAutoGenerateTextMcpProtocolCore::McpProtocolToolAnnotations{});
        // Tool title has priority over annotations title (MCP 2025-06-18)
        tool.displayName = mcpTool.title().value_or(annotations.title().value_or(QString()));
        tool.risk = toolRisk(annotations);
        if (const auto meta = mcpTool.meta(); meta.has_value() && meta->meta().has_value()) {
            const auto values = *meta->meta();
            tool.groupName = values.value(TextAutoGenerateTextMcpProtocolCore::McpProtocolCommonUtils::metaGroupName()).toString();
            tool.groupTitle = values.value(TextAutoGenerateTextMcpProtocolCore::McpProtocolCommonUtils::metaGroupTitle()).toString();
        }
        tools.append(std::move(tool));
        // Next tools of this server must not use same name
        it->tools = tools;
    }
    // Descriptions refer to other tools of server: use names which LLM can call
    for (auto &tool : tools) {
        tool.description = replaceToolNames(tool.description, tools);
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

QString TextAutoGenerateMcpToolsManager::replaceToolNames(const QString &text, const QList<McpTool> &tools)
{
    static const QRegularExpression notCommonWord(u"[_\\-0-9]|.\\p{Lu}"_s);
    QHash<QString, QString> exposedNames;
    QStringList patterns;
    for (const auto &tool : tools) {
        const QString exposedName = QString::fromLatin1(tool.exposedName);
        if (tool.name == exposedName || !tool.name.contains(notCommonWord)) {
            continue;
        }
        exposedNames.insert(tool.name, exposedName);
        patterns.append(QRegularExpression::escape(tool.name));
    }
    if (patterns.isEmpty() || text.isEmpty()) {
        return text;
    }
    // Longest names first: a name can be a prefix of another one
    std::sort(patterns.begin(), patterns.end(), [](const QString &left, const QString &right) {
        return left.size() > right.size();
    });
    // Whole words only, it doesn't change names which are already exposed names
    const QRegularExpression re(u"(?<![\\w-])(?:"_s + patterns.join(u'|') + u")(?![\\w-])"_s, QRegularExpression::UseUnicodePropertiesOption);
    QString result;
    qsizetype position = 0;
    auto it = re.globalMatch(text);
    while (it.hasNext()) {
        const QRegularExpressionMatch match = it.next();
        result += QStringView(text).mid(position, match.capturedStart() - position);
        result += exposedNames.value(match.captured());
        position = match.capturedEnd();
    }
    if (position == 0) {
        return text;
    }
    result += QStringView(text).mid(position);
    return result;
}

QString TextAutoGenerateMcpToolsManager::replaceToolNames(const QByteArray &serverIdentifier, const QString &text) const
{
    return replaceToolNames(text, tools(serverIdentifier));
}

QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolRoot> TextAutoGenerateMcpToolsManager::convertToRoots(const QStringList &paths)
{
    QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolRoot> roots;
    roots.reserve(paths.count());
    for (const QString &path : paths) {
        if (path.trimmed().isEmpty()) {
            continue;
        }
        const QString cleanPath = QDir::cleanPath(QDir::fromNativeSeparators(path.trimmed()));
        TextAutoGenerateTextMcpProtocolCore::McpProtocolRoot root;
        root.setUri(QUrl::fromLocalFile(cleanPath).toString());
        if (const QString name = QDir(cleanPath).dirName(); !name.isEmpty()) {
            root.setName(name);
        }
        roots.append(std::move(root));
    }
    return roots;
}

QByteArray TextAutoGenerateMcpToolsManager::exposedName(const QByteArray &identifier, const QString &serverName, const QString &toolName) const
{
    const auto isUsed = [this](const QByteArray &name) {
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
    const auto it = mServers.constFind(serverIdentifier);
    if (it == mServers.cend()) {
        return {};
    }
    if (!it->server.filterTools()) {
        return it->tools;
    }
    QList<McpTool> list;
    for (const auto &tool : it->tools) {
        if (it->server.isToolAllowed(tool.name)) {
            list.append(tool);
        }
    }
    return list;
}

QList<TextAutoGenerateMcpToolsManager::McpTool> TextAutoGenerateMcpToolsManager::allTools(const QByteArray &serverIdentifier) const
{
    return mServers.value(serverIdentifier).tools;
}

std::optional<TextAutoGenerateMcpToolsManager::McpTool> TextAutoGenerateMcpToolsManager::tool(const QByteArray &exposedName) const
{
    std::optional<McpTool> toolWithSameName;
    bool severalToolsWithSameName = false;
    for (const auto &state : mServers) {
        for (const auto &tool : state.tools) {
            // Tool not allowed can't be called
            if (!state.server.isToolAllowed(tool.name)) {
                continue;
            }
            if (tool.exposedName == exposedName) {
                return tool;
            }
            // LLM can use tool name without server prefix
            if (sanitizeName(tool.name) == exposedName) {
                severalToolsWithSameName = toolWithSameName.has_value();
                toolWithSameName = tool;
            }
        }
    }
    if (severalToolsWithSameName) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Several MCP servers provide tool" << exposedName;
        return std::nullopt;
    }
    return toolWithSameName;
}

QList<QJsonObject> TextAutoGenerateMcpToolsManager::toolsMetaData(const QList<QByteArray> &serverIdentifiers) const
{
    QList<QJsonObject> list;
    for (const QByteArray &identifier : serverIdentifiers) {
        const auto serverTools = tools(identifier);
        for (const auto &tool : serverTools) {
            list.append(toolMetaData(tool));
        }
    }
    return list;
}

QJsonObject TextAutoGenerateMcpToolsManager::toolMetaData(const McpTool &tool)
{
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
    return QJsonObject{{"type"_L1, u"function"_s}, {"function"_L1, functionObj}};
}

QList<TextAutoGenerateMcpToolsManager::McpTool> TextAutoGenerateMcpToolsManager::selectedTools(const QList<QByteArray> &toolIdentifiers) const
{
    QList<McpTool> list;
    const QList<QByteArray> identifiers = serverIdentifiers(toolIdentifiers);
    for (const QByteArray &identifier : identifiers) {
        const auto serverTools = tools(identifier);
        for (const auto &tool : serverTools) {
            if (isToolSelected(tool, toolIdentifiers)) {
                list.append(tool);
            }
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
    const auto serversReady = [this, serverIdentifiers]() {
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
    const auto check = [serversReady, finish]() {
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

QByteArray TextAutoGenerateMcpToolsManager::toolIdentifier(const QByteArray &serverIdentifier, const QString &toolName)
{
    return toolIdentifier(serverIdentifier) + '/' + toolName.toUtf8();
}

bool TextAutoGenerateMcpToolsManager::isMcpToolIdentifier(const QByteArray &toolIdentifier)
{
    return toolIdentifier.startsWith("mcp:");
}

QByteArray TextAutoGenerateMcpToolsManager::serverIdentifier(const QByteArray &toolIdentifier)
{
    if (!isMcpToolIdentifier(toolIdentifier)) {
        return {};
    }
    // Server identifier doesn't contain '/', tool name can contain it
    const qsizetype index = toolIdentifier.indexOf('/', 4);
    return index == -1 ? toolIdentifier.mid(4) : toolIdentifier.mid(4, index - 4);
}

QString TextAutoGenerateMcpToolsManager::toolName(const QByteArray &toolIdentifier)
{
    if (!isMcpToolIdentifier(toolIdentifier)) {
        return {};
    }
    const qsizetype index = toolIdentifier.indexOf('/', 4);
    return index == -1 ? QString() : QString::fromUtf8(toolIdentifier.mid(index + 1));
}

bool TextAutoGenerateMcpToolsManager::isToolSelected(const McpTool &tool, const QList<QByteArray> &toolIdentifiers)
{
    return toolIdentifiers.contains(toolIdentifier(tool.serverIdentifier)) || toolIdentifiers.contains(toolIdentifier(tool.serverIdentifier, tool.name));
}

QList<QByteArray> TextAutoGenerateMcpToolsManager::serverIdentifiers(const QList<QByteArray> &tools)
{
    QList<QByteArray> identifiers;
    for (const QByteArray &tool : tools) {
        if (isMcpToolIdentifier(tool)) {
            if (const QByteArray identifier = serverIdentifier(tool); !identifiers.contains(identifier)) {
                identifiers.append(identifier);
            }
        }
    }
    return identifiers;
}

void TextAutoGenerateMcpToolsManager::setConfirmationHandler(const ConfirmationHandler &handler)
{
    mConfirmationHandler = handler;
}

void TextAutoGenerateMcpToolsManager::setElicitationHandler(const ElicitationHandler &handler)
{
    mElicitationHandler = handler;
}

void TextAutoGenerateMcpToolsManager::setSamplingHandler(const SamplingHandler &handler)
{
    mSamplingHandler = handler;
}

void TextAutoGenerateMcpToolsManager::setPluginProvider(const PluginProvider &provider)
{
    mPluginProvider = provider;
}

bool TextAutoGenerateMcpToolsManager::needConfirmation(const McpTool &tool) const
{
    return mConfirmationHandler && tool.risk != ToolRisk::ReadOnly
        && !TextAutoGenerateText::TextAutoGenerateMcpToolsUtils::isServerAlwaysAllowed(mServerManager->serverConfigFileName(), tool.serverIdentifier);
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
            TextAutoGenerateText::TextAutoGenerateMcpToolsUtils::setServerAlwaysAllowed(mServerManager->serverConfigFileName(), serverIdentifier, true);
        }
        if (guard) {
            callback(confirmation != ToolConfirmation::Deny);
        }
    });
}

bool TextAutoGenerateMcpToolsManager::showUrlElicitations(const QByteArray &serverIdentifier,
                                                          const QList<TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequestURLParams> &elicitations)
{
    if (!mElicitationHandler || elicitations.isEmpty()) {
        return false;
    }
    const QString serverName = mServerManager->mcpServerModel()->mcpServer(serverIdentifier).name();
    for (const auto &params : elicitations) {
        // Not a server request: there is no answer to send
        TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitRequest request;
        request.setParams(params);
        const ElicitationInfo info{
            .serverName = serverName,
            .request = request,
        };
        mElicitationHandler(info, [](const TextAutoGenerateTextMcpProtocolCore::McpProtocolElicitResult &) { });
    }
    return true;
}

McpProtocolClientProtocolManager *TextAutoGenerateMcpToolsManager::client(const QByteArray &serverIdentifier) const
{
    return mServers.value(serverIdentifier).client;
}

#include "moc_textautogeneratemcptoolsmanager.cpp"
