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

QStringList TextAutoGenerateTextToolPluginJob::requiredArguments() const
{
    QStringList lst;
    for (const auto &p : mProperties) {
        lst.append(p.name());
    }
    return lst;
}

bool TextAutoGenerateTextToolPluginJob::verifyRequiredArguments() const
{
    const QStringList requiredArgs = requiredArguments();
    if (mToolArguments.isEmpty() || requiredArgs.isEmpty()) {
        return false;
    }
    if (requiredArgs.count() > mToolArguments.count()) {
        return false;
    }
    for (const auto &arg : requiredArgs) {
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

void TextAutoGenerateTextToolPluginJob::setProperties(const QList<TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty> &newProperties)
{
    mProperties = newProperties;
}

QList<TextAutoGenerateTextToolPluginProperty> TextAutoGenerateTextToolPluginJob::properties() const
{
    return mProperties;
}

bool TextAutoGenerateTextToolPluginJob::canStart() const
{
    if (!verifyRequiredArguments()) {
        qCWarning(TEXTAUTOGENERATETEXT_CORE_LOG) << "missing required arguments";
        return false;
    }
    return !mToolArguments.isEmpty() && !mMessageUuid.isEmpty() && !mToolIdentifier.isEmpty() && !mChatId.isEmpty();
}

QList<TextAutoGenerateReply::ToolCallArgument> TextAutoGenerateTextToolPluginJob::toolArguments() const
{
    return mToolArguments;
}

void TextAutoGenerateTextToolPluginJob::setToolArguments(const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> &newToolArguments)
{
    mToolArguments = newToolArguments;
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
    d.space() << "properties" << t.properties();
    return d;
}

#include "moc_textautogeneratetexttoolpluginjob.cpp"
