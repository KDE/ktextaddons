/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "openaiplugin.h"
using namespace Qt::Literals::StringLiterals;
OpenAIPlugin::OpenAIPlugin(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextPlugin{parent}
{
}

OpenAIPlugin::~OpenAIPlugin() = default;

bool OpenAIPlugin::loadSettings()
{
    // TODO
    return false;
}

void OpenAIPlugin::clear()
{
}

void OpenAIPlugin::setPrompt(const QString &text)
{
    // TODO
}

QString OpenAIPlugin::engineName() const
{
    return name();
}

QString OpenAIPlugin::name()
{
    return "openai"_L1;
}

void OpenAIPlugin::sendToLLM(const SendToLLMInfo &info)
{
    // TODO
}

void OpenAIPlugin::cancelRequest(const QByteArray &uuid)
{
    // TODO
}

#include "moc_openaiplugin.cpp"
