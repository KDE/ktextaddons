/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "mistralplugin.h"

MistralPlugin::MistralPlugin(QObject *parent)
    : TextAutogenerateText::TextAutogenerateTextPlugin{parent}
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

void MistralPlugin::sendToLLM(const QString &message, const QByteArray &uuid)
{
    // TODO
}

void MistralPlugin::cancelRequest(const QByteArray &uuid)
{
    // TODO
}

#include "moc_mistralplugin.cpp"
