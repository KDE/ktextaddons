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

QString MistralPlugin::result()
{
    // TODO
    return {};
}
