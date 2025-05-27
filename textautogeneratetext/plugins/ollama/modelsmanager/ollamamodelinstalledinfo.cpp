/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledinfo.h"
using namespace Qt::Literals::StringLiterals;
OllamaModelInstalledInfo::OllamaModelInstalledInfo() = default;

OllamaModelInstalledInfo::~OllamaModelInstalledInfo() = default;

void OllamaModelInstalledInfo::parseInfo(const QJsonObject &obj)
{
    mName = obj["name"_L1].toString();
    mModel = obj["model"_L1].toString();
    // Details
    const QJsonObject detailsObj = obj["details"_L1].toObject();
    mFamily = detailsObj["family"_L1].toString();
    mQuantizationLevel = detailsObj["quantization_level"_L1].toString();
    mParameterSize = detailsObj["parameter_size"_L1].toString();
}

QString OllamaModelInstalledInfo::parameterSize() const
{
    return mParameterSize;
}

void OllamaModelInstalledInfo::setParameterSize(const QString &newParameterSize)
{
    mParameterSize = newParameterSize;
}

QString OllamaModelInstalledInfo::modifyAt() const
{
    return mModifyAt;
}

void OllamaModelInstalledInfo::setModifyAt(const QString &newModifyAt)
{
    mModifyAt = newModifyAt;
}

QString OllamaModelInstalledInfo::name() const
{
    return mName;
}

void OllamaModelInstalledInfo::setName(const QString &newName)
{
    mName = newName;
}

QString OllamaModelInstalledInfo::model() const
{
    return mModel;
}

void OllamaModelInstalledInfo::setModel(const QString &newModel)
{
    mModel = newModel;
}

QString OllamaModelInstalledInfo::quantizationLevel() const
{
    return mQuantizationLevel;
}

void OllamaModelInstalledInfo::setQuantizationLevel(const QString &newQuantizationLevel)
{
    mQuantizationLevel = newQuantizationLevel;
}

QString OllamaModelInstalledInfo::family() const
{
    return mFamily;
}

void OllamaModelInstalledInfo::setFamily(const QString &newFamily)
{
    mFamily = newFamily;
}

QDebug operator<<(QDebug d, const OllamaModelInstalledInfo &t)
{
    d.space() << "model:" << t.model();
    d.space() << "name:" << t.name();
    d.space() << "quantizationLevel:" << t.quantizationLevel();
    d.space() << "parameterSize:" << t.parameterSize();
    d.space() << "family:" << t.family();
    return d;
}
