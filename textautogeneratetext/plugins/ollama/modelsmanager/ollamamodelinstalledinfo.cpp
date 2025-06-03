/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "ollamamodelinstalledinfo.h"
#include <QLocale>
using namespace Qt::Literals::StringLiterals;
OllamaModelInstalledInfo::OllamaModelInstalledInfo() = default;

OllamaModelInstalledInfo::~OllamaModelInstalledInfo() = default;

void OllamaModelInstalledInfo::parseInfo(const QJsonObject &obj)
{
    mName = obj["name"_L1].toString();
    mModel = obj["model"_L1].toString();
    mModifyAt = obj["modified_at"_L1].toString();
    // Details
    const QJsonObject detailsObj = obj["details"_L1].toObject();
    mFamily = detailsObj["family"_L1].toString();
    mQuantizationLevel = detailsObj["quantization_level"_L1].toString();
    mParameterSize = detailsObj["parameter_size"_L1].toString();
    mParentModel = detailsObj["parent_model"_L1].toString();

    mGeneratedModelName = convertModelNameToDisplay(model());
}

QString OllamaModelInstalledInfo::convertModelNameToDisplay(const QString &modelName)
{
    QString originalModelName = modelName;
    if (modelName.contains(QLatin1Char(':'))) {
        const int position = modelName.indexOf(QLatin1Char(':'));
        originalModelName = modelName.first(position);
    }
    originalModelName = originalModelName.at(0).toUpper() + originalModelName.mid(1, originalModelName.size());
    const QStringList lst = originalModelName.split(QLatin1Char('-'));
    if (lst.count() == 2) {
        const QString secondPart = lst.at(1);
        originalModelName = lst.at(0) + QLatin1Char(' ') + secondPart.at(0).toUpper() + secondPart.mid(1, secondPart.size());
    }
    return originalModelName;
}

QString OllamaModelInstalledInfo::parentModel() const
{
    return mParentModel;
}

void OllamaModelInstalledInfo::setParentModel(const QString &newParentModel)
{
    mParentModel = newParentModel;
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
    d.space() << "parentModel:" << t.parentModel();
    d.space() << "name:" << t.name();
    d.space() << "quantizationLevel:" << t.quantizationLevel();
    d.space() << "parameterSize:" << t.parameterSize();
    d.space() << "family:" << t.family();
    d.space() << "generateModelName:" << t.generateModelName();
    return d;
}

bool OllamaModelInstalledInfo::operator==(const OllamaModelInstalledInfo &other) const
{
    return mName == other.name() && mModel == other.model() && mQuantizationLevel == other.quantizationLevel() && mFamily == other.family()
        && mParameterSize == other.parameterSize() && mModifyAt == other.modifyAt() && mParentModel == other.parentModel();
}

QString OllamaModelInstalledInfo::modifyAtInLocal() const
{
    const QDateTime d = QDateTime::fromString(mModifyAt, Qt::ISODateWithMs);
    return QLocale().toString(d, QLocale::ShortFormat);
}

QString OllamaModelInstalledInfo::generateModelName() const
{
    return mGeneratedModelName;
}
