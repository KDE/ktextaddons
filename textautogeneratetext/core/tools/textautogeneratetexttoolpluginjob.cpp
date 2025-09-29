/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolpluginjob.h"
#include "textautogeneratetextcore_debug.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextToolPluginJob::TextAutoGenerateTextToolPluginJob(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateTextToolPluginJob::~TextAutoGenerateTextToolPluginJob() = default;

void TextAutoGenerateTextToolPluginJob::start()
{
    Q_ASSERT(false);
}

bool TextAutoGenerateTextToolPluginJob::verifyRequiredArguments() const
{
    if (mToolArguments.isEmpty() || mRequiredArguments.isEmpty()) {
        return false;
    }
    if (mRequiredArguments.count() > mToolArguments.count()) {
        return false;
    }
    for (const auto &arg : mRequiredArguments) {
        bool found = false;
        for (const auto &tools : mToolArguments) {
            if (tools.keyTool == arg) {
                found = true;
                break;
            }
        }
        if (!found) {
            return false;
        }
    }
    return true;
}

QByteArray TextAutoGenerateTextToolPluginJob::chatId() const
{
    return mChatId;
}

void TextAutoGenerateTextToolPluginJob::setChatId(const QByteArray &newChatId)
{
    mChatId = newChatId;
}

bool TextAutoGenerateTextToolPluginJob::canStart() const
{
#if 0 // TODO get required arguments
    if (!verifyRequiredArguments()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "missing required arguments";
        return false;
    }
#endif
    return !mToolArguments.isEmpty() && !mMessageUuid.isEmpty() && !mToolIdentifier.isEmpty() /*&& !mRequiredArguments.isEmpty()*/ && !mChatId.isEmpty();
}

QList<TextAutoGenerateReply::ToolCallArgument> TextAutoGenerateTextToolPluginJob::toolArguments() const
{
    return mToolArguments;
}

void TextAutoGenerateTextToolPluginJob::setToolArguments(const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> &newToolArguments)
{
    mToolArguments = newToolArguments;
}

QStringList TextAutoGenerateTextToolPluginJob::requiredArguments() const
{
    return mRequiredArguments;
}

void TextAutoGenerateTextToolPluginJob::setRequiredArguments(const QStringList &newRequiredArguments)
{
    mRequiredArguments = newRequiredArguments;
}

QByteArray TextAutoGenerateTextToolPluginJob::messageUuid() const
{
    return mMessageUuid;
}

void TextAutoGenerateTextToolPluginJob::setMessageUuid(const QByteArray &newMessageUuid)
{
    mMessageUuid = newMessageUuid;
}

QByteArray TextAutoGenerateTextToolPluginJob::toolIdentifier() const
{
    return mToolIdentifier;
}

void TextAutoGenerateTextToolPluginJob::setToolIdentifier(const QByteArray &newToolIdentifier)
{
    mToolIdentifier = newToolIdentifier;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToolPluginJob &t)
{
    d.space() << "toolArguments" << t.toolArguments();
    d.space() << "messageUuid" << t.messageUuid();
    d.space() << "chatId" << t.chatId();
    d.space() << "toolIdentifier" << t.toolIdentifier();
    d.space() << "requiredArguments" << t.requiredArguments();
    return d;
}

#include "moc_textautogeneratetexttoolpluginjob.cpp"
