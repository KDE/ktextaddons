/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetoolcalljob.h"
#include "core/tools/textautogeneratetexttoolinternalinterface.h"
#include "core/tools/textautogeneratetexttoolinternaljob.h"
#include "core/tools/textautogeneratetexttoolplugin.h"
#include "core/tools/textautogeneratetexttoolpluginjob.h"
#include "core/tools/textautogeneratetexttoolpluginmanager.h"
#include "textautogeneratetextcore_debug.h"

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
    for (const auto &i : std::as_const(mInfos)) {
        initializeJob(mChatId, mMessageUuid, i);
    }
}

bool TextAutoGenerateToolCallJob::canStart() const
{
    if (mInfos.isEmpty() || mChatId.isEmpty() || mMessageUuid.isEmpty()) {
        return false;
    }
    return true;
}

void TextAutoGenerateToolCallJob::initializeJob(const QByteArray &chatId,
                                                const QByteArray &uuid,
                                                const TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgumentInfo &info)
{
    const QByteArray toolName = info.toolName;
    auto plugin = TextAutoGenerateTextToolPluginManager::self()->pluginFromToolNameId(toolName);
    if (plugin) {
        auto job = plugin->callTool();
        mListJob.append(job);
        job->setToolArguments(info.toolCallArgument);
        job->setChatId(chatId);
        job->setMessageUuid(uuid);
        job->setToolIdentifier(toolName);
        job->setProperties(plugin->properties());
        job->setRequired(plugin->required());
        connect(job,
                &TextAutoGenerateText::TextAutoGenerateTextToolPluginJob::finished,
                this,
                [this, job](const TextAutoGenerateText::TextAutoGenerateTextToolPlugin::TextToolPluginInfo &info) {
                    mResult.append(info.content);
                    // Q_EMIT finished(str, messageUuid, chatId, toolIdentifier);
                    Q_EMIT toolInProgress({});
                    qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << " TextAutoGenerateTextToolPlugin::finished: " << info.content;
                    mListJob.removeAll(job);
                    if (mListJob.isEmpty()) {
                        const TextAutoGenerateText::TextAutoGenerateTextToolPlugin::TextToolPluginInfo newInfo{
                            .content = mResult.join(u'\n'),
                            .messageUuid = info.messageUuid,
                            .chatId = info.chatId,
                            .toolIdentifier = info.toolIdentifier,
                            .attachementInfoList = info.attachementInfoList,
                        };
                        Q_EMIT finished(newInfo);
                        Q_EMIT toolInProgress({});
                        deleteLater();
                    }
                });
        connect(job,
                &TextAutoGenerateText::TextAutoGenerateTextToolPluginJob::toolInProgress,
                this,
                &TextAutoGenerateText::TextAutoGenerateToolCallJob::toolInProgress);
        job->start();
    } else if (mTextAutoGenerateTextToolInternalInterface && mTextAutoGenerateTextToolInternalInterface->hasTools()) {
        if (mTextAutoGenerateTextToolInternalInterface->contains(toolName)) {
            auto job = mTextAutoGenerateTextToolInternalInterface->callTool(toolName);
            mListJob.append(job);
            job->setToolArguments(info.toolCallArgument);
            job->setChatId(chatId);
            job->setMessageUuid(uuid);
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
                    [this, job](const TextAutoGenerateText::TextAutoGenerateTextToolInternalJob::TextToolPluginInfo &info) {
                        mResult.append(info.content);
                        // Q_EMIT finished(str, messageUuid, chatId, toolIdentifier);
                        Q_EMIT toolInProgress({});
                        qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << " TextAutoGenerateTextToolPlugin::finished: " << info.content;
                        mListJob.removeAll(job);
                        if (mListJob.isEmpty()) {
                            const TextAutoGenerateText::TextAutoGenerateTextToolPlugin::TextToolPluginInfo newInfo{
                                .content = mResult.join(u'\n'),
                                .messageUuid = info.messageUuid,
                                .chatId = info.chatId,
                                .toolIdentifier = info.toolIdentifier,
                                .attachementInfoList = info.attachementInfoList,
                            };
                            Q_EMIT finished(newInfo);
                            Q_EMIT toolInProgress({});
                            deleteLater();
                        }
                    });

            job->start();
        } else {
            qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << "Tool not found " << toolName;
        }
    } else {
        // Internal tools.
        qCDebug(TEXTAUTOGENERATETEXT_CORE_LOG) << "Tool not found " << toolName;
    }
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
