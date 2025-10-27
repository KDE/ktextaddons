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
            [this, job](const QString &str, const QByteArray &messageUuid, const QByteArray &chatId, const QByteArray &toolIdentifier) {
                mResult.append(str);
                // Q_EMIT finished(str, messageUuid, chatId, toolIdentifier);
                Q_EMIT toolInProgress({});
                qDebug() << " TextAutoGenerateTextToolPlugin::finished: " << str;
                mListJob.removeAll(job);
                if (mListJob.isEmpty()) {
                    Q_EMIT finished(mResult.join(u'\n'), messageUuid, chatId, toolIdentifier);
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
