/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetexttoolpluginjob.h"

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

bool TextAutoGenerateTextToolPluginJob::canStart() const
{
    return mToolArguments.isEmpty() && !mMessageUuid.isEmpty();
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

#include "moc_textautogeneratetexttoolpluginjob.cpp"
