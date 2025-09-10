/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "exampletexttoolplugin.h"
#include <KPluginFactory>
using namespace Qt::Literals::StringLiterals;
K_PLUGIN_CLASS_WITH_JSON(ExampleTextToolPlugin, "textautogeneratetext_exampleplugin.json")

ExampleTextToolPlugin::ExampleTextToolPlugin(QObject *parent, const QVariantList &)
    : TextAutoGenerateTextToolPlugin{parent}
{
}

ExampleTextToolPlugin::~ExampleTextToolPlugin() = default;

QString ExampleTextToolPlugin::executeTool()
{
    return {};
}

QString ExampleTextToolPlugin::displayName()
{
    return {};
}

QString ExampleTextToolPlugin::descriptions() const
{
    return {};
}

QJsonObject ExampleTextToolPlugin::metadata() const
{
    return {};
}

#include "exampletexttoolplugin.moc"
#include "moc_exampletexttoolplugin.cpp"
