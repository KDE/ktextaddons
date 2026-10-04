/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetoolcalljob.h"
#include "core/mcp/textautogeneratemcptoolcalljob.h"
#include "core/mcp/textautogeneratemcptoolsmanager.h"
#include "core/tools/textautogeneratetexttoolinternalinterface.h"
#include "core/tools/textautogeneratetexttoolinternaljob.h"
#include "core/tools/textautogeneratetexttoolplugin.h"
#include "core/tools/textautogeneratetexttoolpluginjob.h"
#include "core/tools/textautogeneratetexttoolpluginmanager.h"
#include "textautogeneratetextcore_debug.h"
#include <KLocalizedString>

using namespace TextAutoGenerateText;
TextAutoGenerateToolCallJob::TextAutoGenerateToolCallJob(const QByteArray &chatId,
                                                         const QByteArray &uuid,
                                                         const QList<TextAutoGenerateReply::ToolCallArgumentInfo> &infos,
                                                         QObject *parent)
    : QObject{parent}
    , mChatId(chatId)
    , mMessageUuid(uuid)
    , mInfos(infos)
{
}

TextAutoGenerateToolCallJob::~TextAutoGenerateToolCallJob() = default;

void TextAutoGenerateToolCallJob::start()
{
    if (!canStart()) {
        deleteLater();
        return;
    }
    for (const auto &info : std::as_const(mInfos)) {
        if (auto job = createJob(info)) {
            mListJob.append(job);
        } else {
            qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "Tool not found " << info.toolName;
            mResult.append(i18n("Tool \"%1\" not found.", QString::fromLatin1(info.toolName)));
        }
    }
    if (mListJob.isEmpty()) {
        emitFinished();
        return;
    }
    // Start jobs when all are created: a job can finish synchronously
    const auto jobs = mListJob;
    for (auto job : jobs) {
        job->start();
    }
}

bool TextAutoGenerateToolCallJob::canStart() const
{
    if (mInfos.isEmpty() || mChatId.isEmpty() || mMessageUuid.isEmpty()) {
        return false;
    }
    return true;
}

TextAutoGenerateTextToolBaseJob *TextAutoGenerateToolCallJob::createJob(const TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo &info)
{
    const QByteArray toolName = info.toolName;
    if (auto plugin = TextAutoGenerateTextToolPluginManager::self()->pluginFromToolNameId(toolName); plugin) {
        auto job = plugin->callTool();
        job->setToolArguments(info.toolCallArgument);
        job->setChatId(mChatId);
        job->setMessageUuid(mMessageUuid);
        job->setToolIdentifier(toolName);
        job->setProperties(plugin->properties());
        job->setRequired(plugin->required());
        connect(job,
                &TextAutoGenerateText::TextAutoGenerateTextToolPluginJob::finished,
                this,
                [this, job](const TextAutoGenerateText::TextAutoGenerateTextToolPlugin::TextToolPluginInfo &result) {
                    jobFinished(job, result.content, result.toolIdentifier, result.attachementInfoList);
                });
        connect(job,
                &TextAutoGenerateText::TextAutoGenerateTextToolPluginJob::toolInProgress,
                this,
                &TextAutoGenerateText::TextAutoGenerateToolCallJob::toolInProgress);
        return job;
    }
    if (mTextAutoGenerateTextToolInternalInterface && mTextAutoGenerateTextToolInternalInterface->contains(toolName)) {
        auto job = mTextAutoGenerateTextToolInternalInterface->callTool(toolName);
        job->setToolArguments(info.toolCallArgument);
        job->setChatId(mChatId);
        job->setMessageUuid(mMessageUuid);
        job->setToolIdentifier(toolName);
        const auto toolInternal = mTextAutoGenerateTextToolInternalInterface->toolInternal(toolName);
        job->setProperties(toolInternal.properties());
        job->setRequired(toolInternal.required());
        connect(job,
                &TextAutoGenerateText::TextAutoGenerateTextToolInternalJob::toolInProgress,
                this,
                &TextAutoGenerateText::TextAutoGenerateToolCallJob::toolInProgress);
        connect(job,
                &TextAutoGenerateText::TextAutoGenerateTextToolInternalJob::finished,
                this,
                [this, job](const TextAutoGenerateText::TextAutoGenerateTextToolInternalJob::TextToolPluginInfo &result) {
                    jobFinished(job, result.content, result.toolIdentifier, result.attachementInfoList);
                });
        return job;
    }
    if (mTextAutoGenerateMcpToolsManager && mTextAutoGenerateMcpToolsManager->tool(toolName).has_value()) {
        auto job = new TextAutoGenerateMcpToolCallJob(mTextAutoGenerateMcpToolsManager, this);
        job->setToolArguments(info.toolCallArgument);
        // MCP tools need arguments with their type
        job->setArguments(info.arguments);
        job->setChatId(mChatId);
        job->setMessageUuid(mMessageUuid);
        job->setToolIdentifier(toolName);
        connect(job,
                &TextAutoGenerateText::TextAutoGenerateMcpToolCallJob::finished,
                this,
                [this, job](const TextAutoGenerateText::TextAutoGenerateTextToolPlugin::TextToolPluginInfo &result) {
                    jobFinished(job, result.content, result.toolIdentifier, result.attachementInfoList);
                });
        connect(job,
                &TextAutoGenerateText::TextAutoGenerateMcpToolCallJob::toolInProgress,
                this,
                &TextAutoGenerateText::TextAutoGenerateToolCallJob::toolInProgress);
        return job;
    }
    return nullptr;
}

void TextAutoGenerateToolCallJob::setTextAutoGenerateMcpToolsManager(TextAutoGenerateMcpToolsManager *newTextAutoGenerateMcpToolsManager)
{
    mTextAutoGenerateMcpToolsManager = newTextAutoGenerateMcpToolsManager;
}

void TextAutoGenerateToolCallJob::jobFinished(TextAutoGenerateText::TextAutoGenerateTextToolBaseJob *job,
                                              const QString &content,
                                              const QByteArray &toolIdentifier,
                                              const QList<TextAutoGenerateAttachmentUtils::AttachmentElementInfo> &attachments)
{
    qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << " TextAutoGenerateTextToolPlugin::finished: " << content;
    mResult.append(content);
    mAttachments.append(attachments);
    mToolIdentifier = toolIdentifier;
    Q_EMIT toolInProgress({});
    mListJob.removeAll(job);
    if (mListJob.isEmpty()) {
        emitFinished();
    }
}

void TextAutoGenerateToolCallJob::emitFinished()
{
    const TextAutoGenerateText::TextAutoGenerateTextToolPlugin::TextToolPluginInfo info{
        .content = mResult.join(u'\n'),
        .messageUuid = mMessageUuid,
        .chatId = mChatId,
        .toolIdentifier = mToolIdentifier,
        .attachementInfoList = mAttachments,
    };
    Q_EMIT finished(info);
    Q_EMIT toolInProgress({});
    deleteLater();
}

TextAutoGenerateTextToolInternalInterface *TextAutoGenerateToolCallJob::textAutoGenerateTextToolInternalInterface() const
{
    return mTextAutoGenerateTextToolInternalInterface;
}

void TextAutoGenerateToolCallJob::setTextAutoGenerateTextToolInternalInterface(
    TextAutoGenerateTextToolInternalInterface *newTextAutoGenerateTextToolInternalInterface)
{
    mTextAutoGenerateTextToolInternalInterface = newTextAutoGenerateTextToolInternalInterface;
}

#include "moc_textautogeneratetoolcalljob.cpp"
