/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetexttoolbasejob.h"
#include "textautogeneratetextcore_debug.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextToolBaseJob::TextAutoGenerateTextToolBaseJob(QObject *parent)
    : QObject{parent}
{
}

TextAutoGenerateTextToolBaseJob::~TextAutoGenerateTextToolBaseJob() = default;

QByteArray TextAutoGenerateTextToolBaseJob::chatId() const
{
    return mChatId;
}

void TextAutoGenerateTextToolBaseJob::setChatId(const QByteArray &newChatId)
{
    mChatId = newChatId;
}

QStringList TextAutoGenerateTextToolBaseJob::required() const
{
    return mRequired;
}

void TextAutoGenerateTextToolBaseJob::setRequired(const QStringList &newRequired)
{
    mRequired = newRequired;
}

bool TextAutoGenerateTextToolBaseJob::canStart() const
{
    if (!verifyRequiredArguments()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "missing required arguments";
        return false;
    }
    return !mToolArguments.isEmpty() && !mMessageUuid.isEmpty() && !mToolIdentifier.isEmpty() && !mChatId.isEmpty();
}

QList<TextAutoGenerateReply::ToolCallArgument> TextAutoGenerateTextToolBaseJob::toolArguments() const
{
    return mToolArguments;
}

void TextAutoGenerateTextToolBaseJob::setToolArguments(const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> &newToolArguments)
{
    mToolArguments = newToolArguments;
}

QByteArray TextAutoGenerateTextToolBaseJob::messageUuid() const
{
    return mMessageUuid;
}

void TextAutoGenerateTextToolBaseJob::setMessageUuid(const QByteArray &newMessageUuid)
{
    mMessageUuid = newMessageUuid;
}

QByteArray TextAutoGenerateTextToolBaseJob::toolIdentifier() const
{
    return mToolIdentifier;
}

void TextAutoGenerateTextToolBaseJob::setToolIdentifier(const QByteArray &newToolIdentifier)
{
    mToolIdentifier = newToolIdentifier;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToolBaseJob &t)
{
    d.space() << "toolArguments" << t.toolArguments();
    d.space() << "messageUuid" << t.messageUuid();
    d.space() << "chatId" << t.chatId();
    d.space() << "toolIdentifier" << t.toolIdentifier();
    return d;
}

#include "moc_textautogeneratetexttoolbasejob.cpp"
