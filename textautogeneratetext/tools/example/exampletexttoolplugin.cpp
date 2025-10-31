/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "exampletexttoolplugin.h"
#include "exampletexttoolplugindialog.h"
#include "exampletexttoolpluginjob.h"
#include <KPluginFactory>
K_PLUGIN_CLASS_WITH_JSON(ExampleTextToolPlugin, "textautogeneratetext_exampleplugin.json")

using namespace Qt::Literals::StringLiterals;
ExampleTextToolPlugin::ExampleTextToolPlugin(QObject *parent, const QVariantList &)
    : TextAutoGenerateTextToolPlugin{parent}
{
    mToolNameId = "example_tool"_ba;
    {
        TextAutoGenerateText::TextAutoGenerateTextToolPluginProperty prop;
        prop.setDescription(kli18n("The name of the city"));
        prop.setName(u"city"_s);
        mProperties.append(prop);
    }
}

ExampleTextToolPlugin::~ExampleTextToolPlugin() = default;

QString ExampleTextToolPlugin::displayName() const
{
    // Don't translate it
    return u"Ask Weather Report"_s;
}

QString ExampleTextToolPlugin::description() const
{
    // Don't translate it
    return u"Use this tools, only on meteo. Get the current weather for a city"_s;
}

void ExampleTextToolPlugin::showConfigureDialog(QWidget *parent)
{
    auto dlg = ExampleTextToolPluginDialog(this, parent);
    dlg.exec();
}

TextAutoGenerateText::TextAutoGenerateTextToolPluginJob *ExampleTextToolPlugin::callTool()
{
    return new ExampleTextToolPluginJob(this);
}

int ExampleTextToolPlugin::order() const
{
    return 30;
}

#include "exampletexttoolplugin.moc"
#include "moc_exampletexttoolplugin.cpp"
