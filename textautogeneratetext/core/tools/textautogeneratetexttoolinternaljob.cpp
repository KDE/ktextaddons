/*
  SPDX-FileCopyrightText: 2026 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "textautogeneratetexttoolinternaljob.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextToolInternalJob::TextAutoGenerateTextToolInternalJob(QObject *parent)
    : TextAutoGenerateTextToolBaseJob(parent)
{
}

TextAutoGenerateTextToolInternalJob::~TextAutoGenerateTextToolInternalJob() = default;

void TextAutoGenerateTextToolInternalJob::start()
{
}

bool TextAutoGenerateTextToolInternalJob::canStart() const
{
    // TODO
    return true;
}

bool TextAutoGenerateText::TextAutoGenerateTextToolInternalJob::verifyRequiredArguments() const
{
    // TODO
    return true;
}

QStringList TextAutoGenerateText::TextAutoGenerateTextToolInternalJob::requiredArguments() const
{
    // TODO
    return {};
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextToolInternalJob::TextToolPluginInfo &t)
{
    d.space() << "content" << t.content;
    d.space() << "messageUuid" << t.messageUuid;
    d.space() << "chatId" << t.chatId;
    d.space() << "toolIdentifier" << t.toolIdentifier;
    d.space() << "attachementInfoList" << t.attachementInfoList;
    return d;
}

#include "moc_textautogeneratetexttoolinternaljob.cpp"
