/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "ollamaplugin.h"

OllamaPlugin::OllamaPlugin(QObject *parent)
    : TextAutogenerateText::TextAutogenerateTextPlugin{parent}
{
}

OllamaPlugin::~OllamaPlugin() = default;

bool OllamaPlugin::loadSettings()
{
    // TODO
    return false;
}

void OllamaPlugin::clear()
{
}

QString OllamaPlugin::result()
{
    // TODO
    return {};
}

#include "moc_ollamaplugin.cpp"
