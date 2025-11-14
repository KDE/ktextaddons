/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetoolcalljob.h"
#include "core/tools/textautogeneratetexttoolplugin.h"
#include "core/tools/textautogeneratetexttoolpluginjob.h"
#include "core/tools/textautogeneratetexttoolpluginmanager.h"

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
    auto plugin = TextAutoGenerateTextToolPluginManager::self()->pluginFromToolNameId(info.toolName);
    auto job = plugin->callTool();
    mListJob.append(job);
    job->setToolArguments(info.toolCallArgument);
    job->setChatId(chatId);
    job->setMessageUuid(uuid);
    job->setToolIdentifier(info.toolName);
    job->setProperties(plugin->properties());
    connect(job,
            &TextAutoGenerateText::TextAutoGenerateTextToolPluginJob::finished,
            this,
            [this, job](const TextAutoGenerateText::TextAutoGenerateTextToolPlugin::TextToolPluginInfo &info) {
                mResult.append(info.content);
                // Q_EMIT finished(str, messageUuid, chatId, toolIdentifier);
                Q_EMIT toolInProgress({});
                qDebug() << " TextAutoGenerateTextToolPlugin::finished: " << info.content;
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
}

#include "moc_textautogeneratetoolcalljob.cpp"
