/*
  SPDX-FileCopyrightText: 2025 Laurent Montel <montel@kde.org>

  SPDX-License-Identifier: GPL-2.0-or-later
*/
#include "genericnetworkmodelavailableinfo.h"
using namespace Qt::Literals::StringLiterals;
GenericNetworkModelAvailableInfo::GenericNetworkModelAvailableInfo() = default;

GenericNetworkModelAvailableInfo::~GenericNetworkModelAvailableInfo() = default;

void GenericNetworkModelAvailableInfo::parseInfo(const QJsonObject &obj)
{
    mToolsSupported = obj["tools_supported"_L1].toBool();
    mDescription = obj["description"_L1].toString();
    mModelName = obj["name"_L1].toString();
    // TODO
}

QString GenericNetworkModelAvailableInfo::description() const
{
    return mDescription;
}

void GenericNetworkModelAvailableInfo::setDescription(const QString &newDescription)
{
    mDescription = newDescription;
}

bool GenericNetworkModelAvailableInfo::operator==(const GenericNetworkModelAvailableInfo &other) const
{
    return mDescription == other.description() && mModelName == other.modelName() && mToolsSupported == other.toolsSupported();
}

QString GenericNetworkModelAvailableInfo::modelName() const
{
    return mModelName;
}

void GenericNetworkModelAvailableInfo::setModelName(const QString &newName)
{
    mModelName = newName;
}

bool GenericNetworkModelAvailableInfo::toolsSupported() const
{
    return mToolsSupported;
}

void GenericNetworkModelAvailableInfo::setToolsSupported(bool newToolsSupported)
{
    mToolsSupported = newToolsSupported;
}

QDebug operator<<(QDebug d, const GenericNetworkModelAvailableInfo &t)
{
    d.space() << "name:" << t.modelName();
    d.space() << "description:" << t.description();
    d.space() << "toolsSupported:" << t.toolsSupported();
    return d;
}
