/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "exampletexttoolplugin.h"

ExampleTextToolPlugin::ExampleTextToolPlugin(QObject *parent)
    : TextAutoGenerateTextToolPlugin{parent}
{
}

ExampleTextToolPlugin::~ExampleTextToolPlugin() = default;

#include "moc_exampletexttoolplugin.cpp"
