/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "textautogeneratetextinstance.h"

using namespace TextAutoGenerateText;
TextAutoGenerateTextInstance::TextAutoGenerateTextInstance() = default;

TextAutoGenerateTextInstance::~TextAutoGenerateTextInstance() = default;

QString TextAutoGenerateTextInstance::name() const
{
    return mName;
}

void TextAutoGenerateTextInstance::setName(const QString &newName)
{
    mName = newName;
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
    return !mName.isEmpty() && !mPluginName.isEmpty() && !mInstanceUuid.isEmpty() && !mPluginIdentifier.isEmpty();
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

QDebug operator<<(QDebug d, const TextAutoGenerateText::TextAutoGenerateTextInstance &t)
{
    d.space() << "name:" << t.name();
    d.space() << "pluginName:" << t.pluginName();
    d.space() << "pluginIdentifier:" << t.pluginIdentifier();
    d.space() << "instanceUuid:" << t.instanceUuid();
    return d;
}
