/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "exampletexttoolplugin.h"
#include "exampletexttoolplugindialog.h"
#include <KPluginFactory>
#include <QJsonObject>
#include <QPointer>
K_PLUGIN_CLASS_WITH_JSON(ExampleTextToolPlugin, "textautogeneratetext_exampleplugin.json")

using namespace Qt::Literals::StringLiterals;
ExampleTextToolPlugin::ExampleTextToolPlugin(QObject *parent, const QVariantList &)
    : TextAutoGenerateTextToolPlugin{parent}
{
    mToolNameId = "example_tool"_ba;
}

ExampleTextToolPlugin::~ExampleTextToolPlugin() = default;

QString ExampleTextToolPlugin::executeTool()
{
    return {};
}

QString ExampleTextToolPlugin::displayName() const
{
    // Don't translate it
    return u"Example tool"_s;
}

QString ExampleTextToolPlugin::descriptions() const
{
    // Don't translate it
    return u"Tool used for testing"_s;
}

QByteArray ExampleTextToolPlugin::metadata() const
{
    const QByteArray ba = R"({"name": ")" + mToolNameId + R"(",
                               "description": "Get the current weather for a location",
                               "parameters": {
                                 "type": "object",
                                 "properties": {
                                   "location": {
                                     "type": "string",
                                     "description": "The location to get the weather for, e.g. San Francisco, CA"
                                   },
                                   "format": {
                                     "type": "string",
                                     "description": "The format to return the weather in, e.g. 'celsius' or 'fahrenheit'",
                                     "enum": ["celsius", "fahrenheit"]
                                   }
                                 },
                                 "required": ["location", "format"]
                               }
                            })"_ba;
    return ba;
}

void ExampleTextToolPlugin::showConfigureDialog(QWidget *parent) const
{
    QPointer<ExampleTextToolPluginDialog> dlg = new ExampleTextToolPluginDialog(parent);
    if (dlg->exec()) {
        // TODO
    }
    delete dlg;
}

#include "exampletexttoolplugin.moc"
#include "moc_exampletexttoolplugin.cpp"
