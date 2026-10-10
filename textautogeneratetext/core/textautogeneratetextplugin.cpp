/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetextplugin.h"
#include "core/mcp/textautogeneratemcptoolsmanager.h"
#include "core/models/textautogeneratemessagesmodel.h"
#include "core/textautogeneratemanager.h"
#include "core/textautogeneratemessage.h"
#include "core/textautogeneratereply.h"
#include "core/textautogeneratetextinstance.h"
#include "core/tools/textautogeneratetoolcalljob.h"
#include "textautogeneratetextcore_debug.h"
#include <KLocalizedString>

#include <QDateTime>
#include <QJsonObject>
#include <QPointer>
#include <QUuid>

using namespace TextAutoGenerateText;
using namespace Qt::Literals::StringLiterals;
namespace
{
// Maximum number of requests with tool results for one answer
constexpr int maxToolTurns = 10;
}
class TextAutoGenerateText::TextAutoGenerateTextPluginPrivate
{
public:
    explicit TextAutoGenerateTextPluginPrivate(TextAutoGenerateManager *manager_, TextAutoGenerateText::TextAutoGenerateTextInstance *instance_)
        : manager(manager_)
        , instance(instance_)
    {
    }
    bool hasError = false;
    bool isReady = false;
    // Running tool calls by message uuid
    QHash<QByteArray, QPointer<TextAutoGenerateToolCallJob>> toolCallJobs;
    TextAutoGenerateManager *const manager;
    TextAutoGenerateText::TextAutoGenerateTextInstance *const instance;
};

TextAutoGenerateTextPlugin::TextAutoGenerateTextPlugin(TextAutoGenerateManager *manager,
                                                       TextAutoGenerateText::TextAutoGenerateTextInstance *instance,
                                                       QObject *parent)
    : QObject{parent}
    , d(new TextAutoGenerateText::TextAutoGenerateTextPluginPrivate(manager, instance))
{
}

TextAutoGenerateTextPlugin::~TextAutoGenerateTextPlugin() = default;

TextAutoGenerateTextPlugin::ActivateInstanceActionInfo TextAutoGenerateTextPlugin::activateInstanceAction()
{
    return {};
}

QByteArray TextAutoGenerateTextPlugin::instanceUuid() const
{
    // qDebug() << " d->instance " << d->instance;
    if (!d->instance) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Instance is null in TextAutoGenerateTextPlugin";
        return {};
    }
    return d->instance->instanceUuid();
}

void TextAutoGenerateTextPlugin::load([[maybe_unused]] const KConfigGroup &config)
{
    // reimpl
}

void TextAutoGenerateTextPlugin::save([[maybe_unused]] KConfigGroup &config)
{
    // reimpl
}

void TextAutoGenerateTextPlugin::remove()
{
    // reimpl
}

QList<TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier> TextAutoGenerateTextPlugin::models() const
{
    return mModels;
}

void TextAutoGenerateTextPlugin::setHasError(bool error)
{
    d->hasError = error;
}

bool TextAutoGenerateTextPlugin::ready() const
{
    return d->isReady;
}

void TextAutoGenerateTextPlugin::setReady(bool newReady)
{
    d->isReady = newReady;
    Q_EMIT initializedDone();
}

QJsonArray TextAutoGenerateTextPlugin::createListMessages(const QList<QJsonObject> &objs) const
{
    QList<QJsonObject> lstObj;
    if (const auto obj = createPromptMessage(); !obj.isEmpty()) {
        lstObj.append(obj);
    }
    lstObj += objs;
    QJsonArray array;
    for (const auto &o : std::as_const(lstObj)) {
        array.append(o);
    }
    return array;
}

void TextAutoGenerateTextPlugin::editMessage(const EditSendInfo &editSendInfo)
{
    if (ready()) {
        if (auto messageModel = d->manager->messagesModelFromChatId(editSendInfo.chatId); messageModel) {
            const QByteArray llmUuid = messageModel->editMessage(editSendInfo.messageUuid, editSendInfo.message);

            SendToAssistantInfo info;
            info.message = editSendInfo.message;
            info.messageUuid = llmUuid;
            info.chatId = editSendInfo.chatId;
            info.messagesArray = createListMessages(messageModel->convertToOllamaChat(hasSystemMessageSupport(), hasTextOnlySupport(), toolCallFormat()));
            info.tools = editSendInfo.tools;

            initializeProgress(info);
        } else {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Impossible to find model for chatId:" << editSendInfo.chatId;
        }
    }
}

void TextAutoGenerateTextPlugin::initializeProgress(const SendToAssistantInfo &info)
{
    // Start progress
    d->manager->changeInProgress(info.chatId, info.messageUuid, true);
    TextAutoGenerateAnswerInfo answerInfo;
    answerInfo.setEngineName(engineName());
    answerInfo.setModelName(currentModel());
    answerInfo.setInstanceName(d->instance->displayName());
    answerInfo.setTools(info.tools);
    d->manager->updateMessageInfo(info.chatId, info.messageUuid, answerInfo);
    // Tools of MCP servers must be loaded before sending request
    if (const QList<QByteArray> mcpServers = TextAutoGenerateMcpToolsManager::serverIdentifiers(info.tools); !mcpServers.isEmpty()) {
        d->manager->textAutoGenerateMcpToolsManager()->prepareServers(mcpServers, this, [this, info]() {
            sendToAssistant(info);
        });
        return;
    }
    sendToAssistant(info);
}

TextAutoGenerateMessage::ToolCallFormat TextAutoGenerateTextPlugin::toolCallFormat() const
{
    return TextAutoGenerateMessage::ToolCallFormat::OpenAI;
}

void TextAutoGenerateTextPlugin::processToolCalls(const SendToAssistantInfo &info, const TextAutoGenerateText::TextAutoGenerateReply::Response &response)
{
    QList<TextAutoGenerateReply::ToolCallArgumentInfo> toolCalls = response.info;
    // Ollama doesn't send id, it's needed to associate result with tool call
    for (int i = 0; i < toolCalls.count(); ++i) {
        if (toolCalls.at(i).id.isEmpty()) {
            toolCalls[i].id = "call_" + QByteArray::number(info.toolTurn) + '_' + QByteArray::number(i);
        }
    }
    if (info.toolTurn >= maxToolTurns) {
        // Avoid infinite loop: show results of last tools
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Too many tool calls for message" << info.messageUuid;
        d->toolCallJobs.insert(info.messageUuid, d->manager->callTools(info.chatId, info.messageUuid, toolCalls));
        return;
    }
    auto job = d->manager->createToolCallJob(info.chatId, info.messageUuid, toolCalls);
    d->toolCallJobs.insert(info.messageUuid, job);
    connect(job,
            &TextAutoGenerateToolCallJob::toolResults,
            this,
            [this, info, toolCalls, content = response.response](const QList<QPair<QByteArray, QString>> &results) {
                d->toolCallJobs.remove(info.messageUuid);
                auto messageModel = d->manager->messagesModelFromChatId(info.chatId);
                if (!messageModel) {
                    qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Impossible to find model for chatId:" << info.chatId;
                    return;
                }
                messageModel->appendToolExchange(info.messageUuid, content, toolCalls, results);
                // Send results to LLM
                SendToAssistantInfo nextInfo = info;
                ++nextInfo.toolTurn;
                nextInfo.messagesArray =
                    createListMessages(messageModel->convertToOllamaChat(hasSystemMessageSupport(), hasTextOnlySupport(), toolCallFormat()));
                sendToAssistant(nextInfo);
            });
    connect(job,
            &TextAutoGenerateToolCallJob::finished,
            this,
            [this, info](const TextAutoGenerateText::TextAutoGenerateTextToolPlugin::TextToolPluginInfo &result) {
                // Files created by tools are shown with answer
                if (!result.attachementInfoList.isEmpty()) {
                    d->manager->replaceContent(info.chatId, info.messageUuid, {}, result.attachementInfoList);
                }
            });
    job->start();
}

TextAutoGenerateText::TextAutoGenerateTextRequest TextAutoGenerateTextPlugin::convertSendToAssistantInfoToTextRequest(const SendToAssistantInfo &info) const
{
    TextAutoGenerateText::TextAutoGenerateTextRequest req;
    req.setModel(currentModel());
    req.setMessages(info.messagesArray);
    req.setTools(info.tools);
    req.setThinking(hasThinkSupport());
    return req;
}

void TextAutoGenerateTextPlugin::sendMessage(const EditSendInfo &editSendInfo)
{
    if (ready()) {
        auto messageModel = d->manager->messagesModelFromChatId(editSendInfo.chatId);
        if (!messageModel) {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << " Model Message not found" << editSendInfo.chatId;
            return;
        }
        // User Message
        TextAutoGenerateMessage msg;
        msg.setSender(TextAutoGenerateMessage::Sender::User);
        msg.setContent(editSendInfo.message);
        TextAutoGenerateAttachments *const atts = TextAutoGenerateAttachmentUtils::createTextAutoGenerateAttachments(
            TextAutoGenerateAttachmentUtils::generateAttachmentFromAttachmentElementInfos(editSendInfo.attachmentInfoList));
        msg.setMessageAttachments(*atts);
        delete atts;
        const auto dt = QDateTime::currentSecsSinceEpoch();
        msg.setDateTime(dt);
        msg.setUuid(QUuid::createUuid().toByteArray(QUuid::Id128));
        msg.generateHtml();

        // qDebug() << " msg*************** " << msg;

        // LLM Message
        TextAutoGenerateMessage msgLlm;
        msgLlm.setInProgress(true);
        msgLlm.setSender(TextAutoGenerateMessage::Sender::Assistant);
        msgLlm.setDateTime(dt);
        msgLlm.setUuid(QUuid::createUuid().toByteArray(QUuid::Id128));
        TextAutoGenerateAnswerInfo answerInfo;
        answerInfo.setEngineName(engineName());
        answerInfo.setModelName(currentModel());
        answerInfo.setInstanceName(d->instance->displayName());
        answerInfo.setTools(editSendInfo.tools);
        msgLlm.setMessageInfo(answerInfo);

        const QByteArray llmUuid = msgLlm.uuid();
        msg.setAnswerUuid(llmUuid);

        d->manager->addMessage(editSendInfo.chatId, msg);
        SendToAssistantInfo info;
        info.message = editSendInfo.message;
        info.messageUuid = llmUuid;
        info.chatId = editSendInfo.chatId;
        info.tools = editSendInfo.tools;

        info.messagesArray = createListMessages(messageModel->convertToOllamaChat(hasSystemMessageSupport(), hasTextOnlySupport(), toolCallFormat()));
        // qDebug() << "info.messagesArray  " << info.messagesArray;

        d->manager->addMessage(info.chatId, msgLlm);
        // qDebug() << " info " << info;
        initializeProgress(info);
    } else {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Plugin is not valid:";
    }
}

QJsonObject TextAutoGenerateTextPlugin::createPromptMessage() const
{
    if (!d->manager->systemPrompt().isEmpty() || !shareNamePrompt().isEmpty()) {
        QJsonObject obj;
        obj["role"_L1] = u"system"_s;
        const QString prompt = shareNamePrompt() + d->manager->systemPrompt();
        obj["content"_L1] = prompt;
        return obj;
    }
    return QJsonObject();
}

TextAutoGenerateManager *TextAutoGenerateTextPlugin::manager() const
{
    return d->manager;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextPlugin::SendToAssistantInfo &t)
{
    d.space() << "message:" << t.message;
    d.space() << "messageUuid:" << t.messageUuid;
    d.space() << "chatId:" << t.chatId;
    d.space() << "messagesArray:" << t.messagesArray;
    d.space() << "tools:" << t.tools;
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier &t)
{
    d.space() << "modelName:" << t.modelName;
    d.space() << "identifier:" << t.identifier;
    return d;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextPlugin::EditSendInfo &t)
{
    d.space() << "message:" << t.message;
    d.space() << "messageUuid:" << t.messageUuid;
    d.space() << "chatId:" << t.chatId;
    d.space() << "tools:" << t.tools;
    d.space() << "attachmentList:" << t.attachmentInfoList;
    return d;
}

bool TextAutoGenerateTextPlugin::ModelInfoNameAndIdentifier::isValid() const
{
    return !modelName.isEmpty() && !identifier.isEmpty();
}

void TextAutoGenerateTextPlugin::cancelToolCalls(const QByteArray &uuid)
{
    if (uuid.isEmpty()) {
        const auto jobs = d->toolCallJobs;
        d->toolCallJobs.clear();
        for (const auto &job : jobs) {
            if (job) {
                job->cancel();
            }
        }
    } else if (const auto job = d->toolCallJobs.take(uuid); job) {
        job->cancel();
    }
}

void TextAutoGenerateTextPlugin::clear()
{
    cancelToolCalls({});
    for (auto it = mConnections.keyValueBegin(); it != mConnections.keyValueEnd(); ++it) {
        auto reply = it->first; // TextAutoGenerateText::TextAutoGenerateReply*
        const auto &connection = it->second; // QPair<QByteArray, QMetaObject::Connection>
        if (reply) {
            reply->cancel();
        }
        disconnect(connection.second);
    }
    mConnections.clear();
}

void TextAutoGenerateTextPlugin::cancelRequest(const QByteArray &uuid)
{
    if (uuid.isEmpty()) {
        clear();
    } else {
        cancelToolCalls(uuid);
        for (auto it = mConnections.keyValueBegin(); it != mConnections.keyValueEnd(); ++it) {
            const auto &connection = it->second; // QPair<QByteArray, QMetaObject::Connection>
            if (connection.first == uuid) {
                auto reply = it->first; // TextAutoGenerateText::TextAutoGenerateReply*
                if (reply) {
                    reply->cancel();
                }
                disconnect(connection.second);
                break;
            }
        }
    }
}

QString TextAutoGenerateTextPlugin::convertEngineType(TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType type)
{
    switch (type) {
    case TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType::Local:
        return i18n("Local");
    case TextAutoGenerateText::TextAutoGenerateTextPlugin::EngineType::Network:
        return i18n("Network");
    }
    Q_UNREACHABLE();
    return {};
}

QString TextAutoGenerateTextPlugin::shareNamePrompt() const
{
    return {};
}

bool TextAutoGenerateTextPlugin::hasSystemMessageSupport() const
{
    return true;
}

bool TextAutoGenerateTextPlugin::hasTextOnlySupport() const
{
    return false;
}

QString TextAutoGenerateTextPlugin::fallBackModel() const
{
    // Fallback to first model
    if (!mModels.isEmpty()) {
        return mModels.constFirst().identifier;
    }
    qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Current model is empty. It will failed to work.";
    return {};
}

#include "moc_textautogeneratetextplugin.cpp"
