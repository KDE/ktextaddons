/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstance.h"
#include "core/textautogeneratetextplugin.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextInstance::TextAutoGenerateTextInstance() = default;

TextAutoGenerateTextInstance::~TextAutoGenerateTextInstance()
{
    // if (mPlugin) {
    // mPlugin->deleteLater();
    // mPlugin = nullptr;
    // }
}

QString TextAutoGenerateTextInstance::displayName() const
{
    if (mPlugin) {
        return mPlugin->displayName();
    }
    return {};
}

QString TextAutoGenerateTextInstance::pluginName() const
{
    return mPluginName;
}

void TextAutoGenerateTextInstance::setPluginName(const QString &newPluginName)
{
    mPluginName = newPluginName;
}

bool TextAutoGenerateTextInstance::isValid() const
{
    return !mPluginName.isEmpty() && !mInstanceUuid.isEmpty() && !mPluginIdentifier.isEmpty();
}

QByteArray TextAutoGenerateTextInstance::instanceUuid() const
{
    return mInstanceUuid;
}

void TextAutoGenerateTextInstance::setInstanceUuid(const QByteArray &newInstanceUuid)
{
    mInstanceUuid = newInstanceUuid;
}

QString TextAutoGenerateTextInstance::pluginIdentifier() const
{
    return mPluginIdentifier;
}

void TextAutoGenerateTextInstance::setPluginIdentifier(const QString &newPluginIdentifier)
{
    mPluginIdentifier = newPluginIdentifier;
}

void TextAutoGenerateTextInstance::load(const KConfigGroup &config)
{
    mEnabled = config.readEntry("enabled", false);
    mPluginName = config.readEntry("pluginName", QString());
    mPluginIdentifier = config.readEntry("pluginIdentifier", QString());
    mInstanceUuid = config.readEntry("uuid", QByteArray());
}

void TextAutoGenerateTextInstance::save(KConfigGroup &config)
{
    config.writeEntry("enabled", mEnabled);
    config.writeEntry("pluginName", mPluginName);
    config.writeEntry("pluginIdentifier", mPluginIdentifier);
    config.writeEntry("uuid", mInstanceUuid);
    if (mPlugin) {
        mPlugin->save(config);
    }
}

QString TextAutoGenerateTextInstance::currentModel() const
{
    if (mPlugin) {
        return mPlugin->currentModel();
    }
    return {};
}

TextAutoGenerateTextPlugin *TextAutoGenerateTextInstance::plugin() const
{
    return mPlugin;
}

void TextAutoGenerateTextInstance::setPlugin(TextAutoGenerateText::TextAutoGenerateTextPlugin *newPlugin)
{
    mPlugin = newPlugin;
}

bool TextAutoGenerateTextInstance::enabled() const
{
    return mEnabled;
}

void TextAutoGenerateTextInstance::setEnabled(bool newEnabled)
{
    mEnabled = newEnabled;
}

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextInstance &t)
{
    d.space() << "pluginName:" << t.pluginName();
    d.space() << "pluginIdentifier:" << t.pluginIdentifier();
    d.space() << "currentModel:" << t.currentModel();
    d.space() << "instanceUuid:" << t.instanceUuid();
    d.space() << "enabled:" << t.enabled();
    return d;
}
