/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mistralplugin.h"
using namespace Qt::Literals::StringLiterals;
MistralPlugin::MistralPlugin(QObject *parent)
    : TextAutoGenerateText::TextAutoGenerateTextPlugin{parent}
{
}

MistralPlugin::~MistralPlugin() = default;

bool MistralPlugin::loadSettings()
{
    // TODO
    return false;
}

void MistralPlugin::clear()
{
}

void MistralPlugin::setPrompt(const QString &text)
{
    // TODO
}

QString MistralPlugin::engineName() const
{
    return name();
}

void MistralPlugin::sendToAssistant(const SendToAssistantInfo &info)
{
    // TODO
}

void MistralPlugin::askToAssistant(const QString &msg)
{
    // TODO
}

void MistralPlugin::cancelRequest(const QByteArray &uuid)
{
    // TODO
}

QString MistralPlugin::name()
{
    return "mistral"_L1;
}

#include "moc_mistralplugin.cpp"
