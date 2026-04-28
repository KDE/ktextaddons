/*
  SPDX-FileCopyrightText: 2026 Florian Richer <florian.richer@protonmail.com>

  SPDX-License-Identifier: GPL-2.0-or-later
*/

#include "lmstudiomodelinstalledinfo.h"
#include "core/textautogeneratemanager.h"
#include "core/tools/textautogeneratetexttoolpluginmanager.h"

#include <QJsonArray>
#include <QStringLiteral>

using namespace Qt::StringLiterals;

LMStudioModelInstalledInfo::LMStudioModelInstalledInfo() = default;
LMStudioModelInstalledInfo::~LMStudioModelInstalledInfo() = default;

QString LMStudioModelInstalledInfo::name() const
{
    return mName;
}

void LMStudioModelInstalledInfo::setName(const QString &newName)
{
    mName = newName;
}

QString LMStudioModelInstalledInfo::publisher() const
{
    return mPublisher;
}

void LMStudioModelInstalledInfo::setPublisher(const QString &newPublisher)
{
    mPublisher = newPublisher;
}

QString LMStudioModelInstalledInfo::model() const
{
    return mModel;
}

void LMStudioModelInstalledInfo::setModel(const QString &newModel)
{
    mModel = newModel;
}

QString LMStudioModelInstalledInfo::quantizationLevel() const
{
    return mQuantizationLevel;
}

void LMStudioModelInstalledInfo::setQuantizationLevel(const QString &newQuantizationLevel)
{
    mQuantizationLevel = newQuantizationLevel;
}

QString LMStudioModelInstalledInfo::parameterSize() const
{
    return mParameterSize;
}

void LMStudioModelInstalledInfo::setParameterSize(const QString &newParameterSize)
{
    mParameterSize = newParameterSize;
}

TextAutoGenerateText::TextAutoGenerateManager::Categories LMStudioModelInstalledInfo::categories() const
{
    return mCategories;
}

void LMStudioModelInstalledInfo::setCategories(TextAutoGenerateText::TextAutoGenerateManager::Categories newCategories)
{
    mCategories = newCategories;
}

void LMStudioModelInstalledInfo::parseInfo(const QJsonObject &obj)
{
    mName = obj["display_name"_L1].toString();
    mPublisher = obj["publisher"_L1].toString();
    mModel = obj["key"_L1].toString();
    mParameterSize = obj["params_string"_L1].toString();

    const QJsonObject quantizationObj = obj["quantization"_L1].toObject();
    if (!quantizationObj.isEmpty()) {
        mQuantizationLevel = quantizationObj["name"_L1].toString();
    }

    const QJsonObject capabilitiesObj = obj["capabilities"_L1].toObject();
    if (!capabilitiesObj.isEmpty()) {
        mCategories &= 0; // Reset all categories
        if (capabilitiesObj.contains("trained_for_tool_use"_L1) && capabilitiesObj["trained_for_tool_use"_L1].toBool()) {
            mCategories |= TextAutoGenerateText::TextAutoGenerateManager::Category::Tools;
        }
        if (capabilitiesObj.contains("vision"_L1) && capabilitiesObj["vision"_L1].toBool()) {
            mCategories |= TextAutoGenerateText::TextAutoGenerateManager::Category::Vision;
        }
        if (capabilitiesObj.contains("reasoning"_L1) && capabilitiesObj["reasoning"_L1].isObject()) {
            mCategories |= TextAutoGenerateText::TextAutoGenerateManager::Category::Reasoning;
        }
    }
}

QDebug operator<<(QDebug d, const LMStudioModelInstalledInfo &t)
{
    d.space() << "model:" << t.model();
    d.space() << "name:" << t.name();
    d.space() << "quantizationLevel:" << t.quantizationLevel();
    d.space() << "parameterSize:" << t.parameterSize();
    d.space() << "categories:" << t.categories();
    return d;
}
