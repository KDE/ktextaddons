/*
  SPDX-FileCopyrightText: 2025-2026 Laurent Montel <montel@kde.org>
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "plugincommonmodelinstalledinfo.h"

QString PluginCommonModelInstalledInfo::name() const
{
    return mName;
}

void PluginCommonModelInstalledInfo::setName(const QString &newName)
{
    mName = newName;
}

QString PluginCommonModelInstalledInfo::model() const
{
    return mModel;
}

void PluginCommonModelInstalledInfo::setModel(const QString &newModel)
{
    mModel = newModel;
}

QString PluginCommonModelInstalledInfo::quantizationLevel() const
{
    return mQuantizationLevel;
}

void PluginCommonModelInstalledInfo::setQuantizationLevel(const QString &newQuantizationLevel)
{
    mQuantizationLevel = newQuantizationLevel;
}

QString PluginCommonModelInstalledInfo::parameterSize() const
{
    return mParameterSize;
}

void PluginCommonModelInstalledInfo::setParameterSize(const QString &newParameterSize)
{
    mParameterSize = newParameterSize;
}

TextAutoGenerateText::TextAutoGenerateManager::Categories PluginCommonModelInstalledInfo::categories() const
{
    return mCategories;
}

void PluginCommonModelInstalledInfo::setCategories(TextAutoGenerateText::TextAutoGenerateManager::Categories newCategories)
{
    mCategories = newCategories;
}

QDebug operator<<(QDebug d, const PluginCommonModelInstalledInfo &t)
{
    d.space() << "model:" << t.model();
    d.space() << "name:" << t.name();
    d.space() << "quantizationLevel:" << t.quantizationLevel();
    d.space() << "parameterSize:" << t.parameterSize();
    d.space() << "categories:" << t.categories();
    return d;
}
