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
    return mToolArguments.isEmpty();
}

QList<TextAutoGenerateReply::ToolCallArgument> TextAutoGenerateTextToolPluginJob::toolArguments() const
{
    return mToolArguments;
}

void TextAutoGenerateTextToolPluginJob::setToolArguments(const QList<TextAutoGenerateText::TextAutoGenerateReply::ToolCallArgument> &newToolArguments)
{
    mToolArguments = newToolArguments;
}

#include "moc_textautogeneratetexttoolpluginjob.cpp"
