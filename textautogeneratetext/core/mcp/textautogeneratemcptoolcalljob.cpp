/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratemcptoolcalljob.h"
#include "core/mcp/textautogeneratemcptoolsmanager.h"
#include "textautogeneratetextcore_debug.h"
#include <KLocalizedString>
#include <QJsonDocument>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolCallToolResult>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolClientProtocolManager>
#include <TextAutoGenerateTextMcpProtocolCore/McpProtocolJSONRPCErrorResponse>

using namespace Qt::Literals::StringLiterals;
using namespace TextAutoGenerateText;
using TextAutoGenerateTextMcpProtocolCore::McpProtocolClientProtocolManager;

TextAutoGenerateMcpToolCallJob::TextAutoGenerateMcpToolCallJob(TextAutoGenerateMcpToolsManager *toolsManager, QObject *parent)
    : TextAutoGenerateTextToolBaseJob{parent}
    , mToolsManager(toolsManager)
{
}

TextAutoGenerateMcpToolCallJob::~TextAutoGenerateMcpToolCallJob() = default;

void TextAutoGenerateMcpToolCallJob::start()
{
    const auto tool = mToolsManager->tool(mToolIdentifier);
    McpProtocolClientProtocolManager *client = tool.has_value() ? mToolsManager->client(tool->serverIdentifier) : nullptr;
    mClient = client;
    if (!client) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "MCP tool not available:" << mToolIdentifier;
        emitFinished(i18n("Tool \"%1\" is not available.", QString::fromLatin1(mToolIdentifier)));
        return;
    }
    connect(client, &McpProtocolClientProtocolManager::received, this, [this](const QJsonObject &obj, McpProtocolClientProtocolManager::MethodType type) {
        if (type != McpProtocolClientProtocolManager::MethodType::CallTool || obj.value("id"_L1).toInteger(-1) != mRequestId) {
            return;
        }
        if (const QJsonValue resultValue = obj.value("result"_L1); resultValue.isObject()) {
            emitFinished(resultToText(TextAutoGenerateTextMcpProtocolCore::McpProtocolCallToolResult::fromJson(resultValue.toObject())));
        } else {
            const auto response = TextAutoGenerateTextMcpProtocolCore::McpProtocolJSONRPCErrorResponse::fromJson(obj);
            emitFinished(i18n("Error: %1", response.error().message()));
        }
    });
    // Server stopped before answering
    connect(client, &McpProtocolClientProtocolManager::finished, this, [this]() {
        emitFinished(i18n("Error: server was stopped."));
    });
    // User must accept tool call
    mToolsManager->confirmToolCall(*tool, mArguments, this, [this, name = tool->name](bool accepted) {
        if (mFinished) {
            return;
        }
        if (!accepted) {
            emitFinished(i18n("User refused to run tool \"%1\".", name));
            return;
        }
        if (!mClient) {
            emitFinished(i18n("Error: server was stopped."));
            return;
        }
        Q_EMIT toolInProgress(i18n("Calling tool \"%1\"…", name));
        mRequestId = mClient->callTool(name, mArguments);
        if (mRequestId == -1) {
            emitFinished(i18n("Error: impossible to call tool \"%1\".", name));
        }
    });
}

void TextAutoGenerateMcpToolCallJob::cancel()
{
    if (mFinished) {
        return;
    }
    mFinished = true;
    if (mClient) {
        mClient->disconnect(this);
        if (mRequestId != -1) {
            mClient->cancelRequest(mRequestId, u"Cancelled by user"_s);
        }
    }
    deleteLater();
}

void TextAutoGenerateMcpToolCallJob::emitFinished(const QString &content)
{
    if (mFinished) {
        return;
    }
    mFinished = true;
    if (mClient) {
        mClient->disconnect(this);
    }
    const TextAutoGenerateTextToolPlugin::TextToolPluginInfo info{
        .content = content,
        .messageUuid = mMessageUuid,
        .chatId = mChatId,
        .toolIdentifier = mToolIdentifier,
        .attachementInfoList = {},
    };
    Q_EMIT finished(info);
    deleteLater();
}

QString TextAutoGenerateMcpToolCallJob::resultToText(const TextAutoGenerateTextMcpProtocolCore::McpProtocolCallToolResult &result)
{
    QStringList texts;
    const auto contents = result.content();
    for (const auto &content : contents) {
        std::visit(
            [&texts](const auto &block) {
                using T = std::decay_t<decltype(block)>;
                if constexpr (std::is_same_v<T, TextAutoGenerateTextMcpProtocolCore::McpProtocolTextContent>) {
                    texts.append(block.text());
                } else if constexpr (std::is_same_v<T, TextAutoGenerateTextMcpProtocolCore::McpProtocolResourceLink>) {
                    texts.append(block.uri());
                } else if constexpr (std::is_same_v<T, TextAutoGenerateTextMcpProtocolCore::McpProtocolEmbeddedResource>) {
                    const auto resource = block.resource();
                    if (const auto textResource = std::get_if<TextAutoGenerateTextMcpProtocolCore::McpProtocolTextResourceContents>(&resource)) {
                        texts.append(textResource->text());
                    }
                }
                // Image and audio are not supported yet
            },
            content);
    }
    if (texts.isEmpty()) {
        // Structured result only
        if (const auto structuredContent = result.structuredContent(); structuredContent.has_value()) {
            QJsonObject obj;
            for (auto it = structuredContent->cbegin(); it != structuredContent->cend(); ++it) {
                obj.insert(it.key(), it.value());
            }
            texts.append(QString::fromUtf8(QJsonDocument(obj).toJson(QJsonDocument::Compact)));
        }
    }
    QString text = texts.join(u'\n');
    if (result.isError().value_or(false)) {
        text = i18n("Error: %1", text);
    }
    return text;
}

QJsonObject TextAutoGenerateMcpToolCallJob::arguments() const
{
    return mArguments;
}

void TextAutoGenerateMcpToolCallJob::setArguments(const QJsonObject &newArguments)
{
    mArguments = newArguments;
}

#include "moc_textautogeneratemcptoolcalljob.cpp"
